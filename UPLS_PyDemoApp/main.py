# This Python file uses the following encoding: utf-8
import sys

from UPLS import UPLS_Controller, HookInfo, LandingGearInfo
from tkinter import *
from tkinter import ttk
from custom_widgets import HookInfoWidget, LandingGearInfoWidget, WinchInfoWidget

class ChooseSerialBox:
	def __init__(self, root = Tk, parent = 0, title=""):
		self.start_success = False
		self.str_portName = ""
		self.lst_AvailablePorts = []
		self.win_Window = Toplevel()
		self.win_Window.title(title)
		
		if parent:
			x = int(parent.winfo_x() + parent.winfo_width() / 2 - 90)
			y = int(parent.winfo_y() + parent.winfo_height() / 2 - 50)
			self.win_Window.geometry("180x100+" + str(x) + "+" + str(y))
		else:
			self.win_Window.geometry("180x100+300+300")

		self.win_Window.resizable(False, False)
		self.win_Window.protocol("WM_DELETE_WINDOW", self.__onClosing)
		self.lbl_Top = Label(self.win_Window, text = "Choose serial port:")
		self.cmb_PortSelection = ttk.Combobox(self.win_Window, values=[], state="readonly", 
												postcommand=self.__updatePortSelection)
		self.btn_Button = Button(self.win_Window, text="Connect", command=self.__onButtonClick, state="disabled")
		self.lbl_Top.grid(column=0, row=0)
		self.cmb_PortSelection.grid(column=0, row=1)
		self.btn_Button.grid(column=0, row=2)

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
			print("No ports found.")
			self.win_Window.destroy()
		else:
			self.str_portName = self.lst_AvailablePorts[self.cmb_PortSelection.current()]
			print("Selected: ", self.str_portName)
			self.win_Window.destroy()
			self.start_success = True

	def run(self):
		print("entering from mainloop")
		self.win_Window.mainloop()
		
	def success(self):
		return self.success

	def getSelectedPort(self):
		return self.str_portName		


class MainApp:
	def __init__(self, title = "App"):
		self.b_ececutePeriodicTasks = False

		self.root = Tk()
		self.root.withdraw()

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

	def __onClosing(self):
		self.__onDisconnect()
		self.root.destroy()
		sys.exit()

	def __enableWidgets(self, enable = True):
		self.b_ececutePeriodicTasks = enable
		state = str()
		if enable:
			state = "readonly"
			self.hki_HookInfo.state("readonly")
			self.lgi_LandingGearInfo.state("readonly")
			self.wni_WinchInfo.state("readonly")
		else:
			state = "disabled"
			self.hki_HookInfo.state("disabled")
			self.lgi_LandingGearInfo.state("disabled")
			self.wni_WinchInfo.state("disabled")

	def __resetWidgets(self):
		self.hki_HookInfo.update()
		self.lgi_LandingGearInfo.update()
		self.wni_WinchInfo.update()

	def __onChooseSerial(self):
		self.__enableWidgets(False)
		choose_serial = ChooseSerialBox(root=self.root, parent=self.win_Info, title="Choose serial port")
		choose_serial.run()

		if choose_serial.success():
			print("Success!")
			self.__enableWidgets()
		else:
			self.__onDisconnect()

	def __onDisconnect(self):
		print("entring __onDisconnect")
		self.__resetWidgets()
		self.__enableWidgets(False)

	def __periodicalTasks(self):
		if self.b_ececutePeriodicTasks:
			print("periodic")
		
		self.root.after(1000, self.__periodicalTasks)

	def run(self):
		
		self.root.after(1000, self.__periodicalTasks)
		self.root.mainloop()
		#while self.running:
		#	self.win_Info.update_idletasks()
		#	self.win_Info.update()			
		#	
		#	self.win_Command.update_idletasks()
		#	self.win_Command.update()	

#			if upls.messagesReceived():
#				upls.printAllMessages()
#
#			if upls.errorsOccured():
#				upls.printAllErrors()
#				upls.clearAllErrors()
#
#			if upls.warningsReceived():
#				upls.printAllWarnings()
#				upls.clearAllWarnings()


if __name__ == "__main__":
	main_app = MainApp("Demo")
	main_app.run()

