# This Python file uses the following encoding: utf-8
import sys

from UPLS import *
from tkinter import *
from tkinter import ttk
from custom_widgets import HookInfoWidget, LandingGearInfoWidget, WinchInfoWidget

class ChooseSerialBox:
	def __init__(self, parent = 0, title="", on_destruction = 0):
		self.running = False
		self.parent = parent
		self.start_success = False
		self.str_portName = ""
		self.lst_AvailablePorts = []
		
		self.win_Window = Tk()
		self.win_Window.title(title)

		self.win_Window.protocol("WM_DELETE_WINDOW", self.__onClosing)
		self.lbl_Top = Label(self.win_Window, text = "Choose serial port:")
		self.cmb_PortSelection = ttk.Combobox(self.win_Window, values=[], state="readonly", 
												postcommand=self.__updatePortSelection)
		self.btn_Button = Button(self.win_Window, text="Connect", command=self.__onButtonClick, state="disabled")
		self.lbl_Top.grid(column=0, row=0)
		self.cmb_PortSelection.grid(column=0, row=1)
		self.btn_Button.grid(column=0, row=2)

		self.win_Window.resizable(False, False)

		self.callback = on_destruction

	def __onClosing(self):
		self.win_Window.destroy()

	def __updatePortSelection(self):
		self.lst_AvailablePorts = UPLS_Controller().listAvailablePorts()
		self.cmb_PortSelection["values"] = self.lst_AvailablePorts
		if self.lst_AvailablePorts:
			self.cmb_PortSelection.current(0)
			self.btn_Button["state"] = "normal"

	def __onButtonClick(self):
		if not self.lst_AvailablePorts:
			self.win_Window.destroy()
			if self.callback:
				self.callback()
		else:
			self.start_success = True
			self.str_portName = self.lst_AvailablePorts[self.cmb_PortSelection.current()]
			self.win_Window.destroy()
			if self.callback:
				self.callback()

	def run(self):
		if self.parent:
			self.win_Window.update()
			width = self.win_Window.winfo_width()
			height = self.win_Window.winfo_height()
			x = int(self.parent.winfo_x() + (self.parent.winfo_width() - width) / 2)
			y = int(self.parent.winfo_y() + (self.parent.winfo_height() - height) / 2)
			self.win_Window.geometry(str(width) + "x" + str(height) + "+" + str(x) + "+" + str(y))
		
		self.running = True
		self.win_Window.mainloop()
		
	def success(self):
		return self.start_success

	def getSelectedPort(self):
		return self.str_portName		


class MainApp:
	def __init__(self, title = "App"):
		self.b_ececutePeriodicTasks = False

		self.root = Tk()
		self.root.withdraw()

		self.upls = UPLS_Controller()
		self.choose_serial = 0

		# info window
		self.win_Info = Toplevel()
		self.win_Info.title(title + ": Info")
		#self.win_Info.geometry("400x300+300+300")
		self.win_Info.resizable(False, False)
		self.win_Info.protocol("WM_DELETE_WINDOW", self.__onClosing)
		self.mnb_MenuBar = Menu(self.win_Info)
		self.hki_HookInfo = HookInfoWidget(self.win_Info)
		self.lgi_LandingGearInfo = LandingGearInfoWidget(self.win_Info)
		self.wni_WinchInfo = WinchInfoWidget(self.win_Info)

		self.hki_HookInfo.grid(column=0, row=0, padx=5, pady=5)
		self.lgi_LandingGearInfo.grid(column=0, row=1, padx=5, pady=5)
		self.wni_WinchInfo.grid(column=0, row=2, padx=5, pady=5)

		self.mnb_MenuBar.add_command(label="Choose & Connect...", command=self.__onChooseSerial)
		self.mnb_MenuBar.add_command(label="Disconnect", command=self.__onDisconnect)
		self.mnb_MenuBar.add_separator()
		self.mnb_MenuBar.add_command(label="Exit", command=self.__onClosing)

		self.win_Info.config(menu = self.mnb_MenuBar)

		#command window

		self.win_Command = Toplevel()
		self.win_Command.title(title + ": Commands")
		self.win_Command.resizable(False, False)
		self.win_Command.protocol("WM_DELETE_WINDOW", self.__onClosing)
		self.btn_ledOn = Button(self.win_Command, state="disabled", text="Led On", command=self.upls.ledOn)
		self.btn_ledOff = Button(self.win_Command, state="disabled", text="Led Off", command=self.upls.ledOff)

		self.btn_ledOn.grid(column=0, row=0)
		self.btn_ledOff.grid(column=0, row=1)

	def __onClosing(self):
		self.__onDisconnect()
		self.root.destroy()

	def __enableCommands(self, enable = True):
		if enable:
			self.btn_ledOn["state"] = "normal"
			self.btn_ledOff["state"] = "normal"
		else:
			self.btn_ledOn["state"] = "disabled"
			self.btn_ledOff["state"] = "disabled"

	def __enableWidgets(self, enable = True):
		self.b_ececutePeriodicTasks = enable

		self.__enableCommands(enable)

		if enable:
			self.hki_HookInfo.state("readonly")
			self.lgi_LandingGearInfo.state("readonly")
			self.wni_WinchInfo.state("readonly")
		else:
			self.hki_HookInfo.state("disabled")
			self.lgi_LandingGearInfo.state("disabled")
			self.wni_WinchInfo.state("disabled")

	def __resetWidgets(self):
		self.hki_HookInfo.updateVal()
		self.lgi_LandingGearInfo.updateVal()
		self.wni_WinchInfo.updateVal()

	def __onChooseSerialExit(self):
		if self.choose_serial.success():
			print("Success!")
			self.upls.setSerialPort(self.choose_serial.getSelectedPort())
			self.upls.start()
			self.__enableWidgets()
		else:
			self.__onDisconnect()

	def __onChooseSerial(self):
		self.__enableWidgets(False)
		self.choose_serial = ChooseSerialBox(parent=self.win_Info, title="Choose serial port", on_destruction=self.__onChooseSerialExit)
		self.choose_serial.run()

	def __onDisconnect(self):
		self.upls.stop()
		self.__enableWidgets(False)
		self.__resetWidgets()

	def __periodicalTasks(self):
		if self.upls.messagesReceived():
			self.upls.printAllMessages()
		
		if self.upls.errorsOccured():
			self.upls.printAllErrors()
			self.upls.clearAllErrors()
		
		if self.upls.warningsReceived():
			self.upls.printAllWarnings()
			self.upls.clearAllWarnings()

		self.hki_HookInfo.updateVal(self.upls.hookInfo(), self.upls.hookInfoUpdateFrequency())
		self.lgi_LandingGearInfo.updateVal(self.upls.landingGearInfo(), self.upls.landingGearInfoUpdateFrequency())
		self.wni_WinchInfo.updateVal(self.upls.winchInfo(), self.upls.winchInfoUpdateFrequency())

	def __executePeriodicalTasks(self):
		if self.b_ececutePeriodicTasks:
			self.__periodicalTasks()
		
		self.root.after(100, self.__executePeriodicalTasks)

	def run(self):
		self.root.after(100, self.__executePeriodicalTasks)
		self.root.mainloop()
		


if __name__ == "__main__":
	main_app = MainApp(title = "Demo")
	main_app.run()
