# This Python file uses the following encoding: utf-8
import sys

from UPLS import *
from tkinter import *
from tkinter import ttk

from custom_widgets import HookInfoWidget

#lst_AvailablePorts = [ "dev/ttyACM0", "dev/ttyUSB0", "dev/ttyUSB1" ]

app_name = "Demo"

class StartApp:
	def __init__(self):
		self.start_success = False
		self.str_portName = ""
		self.lst_AvailablePorts = []
		self.win_Window = Tk()
		self.win_Window.title(app_name)
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
		self.win_Window.mainloop()
		return self.start_success

	def getSelectedPort(self):
		return self.str_portName		

class MainApp:
	def __init__(self, serial_port = ""):
		if serial_port == "":
			print("[MainApp] serial_port was not specified.\n Exiting...")
			sys.exit()
		self.running = False

		self.win_Window = Tk()
		self.win_Window.title(app_name)
		self.win_Window.geometry("400x300+300+300")
		self.win_Window.resizable(False, False)
		self.win_Window.protocol("WM_DELETE_WINDOW", self.__onClosing)
		self.hki_HookInfo = HookInfoWidget(self.win_Window)

		self.hki_HookInfo.grid(column=0, row=0, padx=2, pady=2)

	def __onClosing(self):
		self.running = False
		self.win_Window.destroy()

	def run(self):
		self.running = True
		while self.running:
			self.win_Window.update_idletasks()
			self.win_Window.update()

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
	#start_app = StartApp()
	#success = start_app.run()
	#
	#if not success:
	#	print("Exiting...")
	#	sys.exit()

	main_app = MainApp("dummy port")
	main_app.run()

	#Main()
#	print("Connecting to: ", portList[0])
#	upls.setSerialPort(portList[0])
#	upls.start()
#
#	win_Main = Tk()
#	win_Main.title("UPLS Test")
#	win_Main.geometry('350x200')
#
#	win_Main.protocol("WM_DELETE_WINDOW", onMainClosing)
#
#	ledOnBtn = Button(win_Main, text="Led On", command=onLedOnButtonClick)
#	ledOffBtn = Button(win_Main, text="Led Off", command=onLedOffButtonClick)
#
#	ledOnBtn.grid(column=0, row=0)
#	ledOffBtn.grid(column=1, row=0)
#
#	print("Closing...")
#	upls.stop()
#
#
#def onLedOnButtonClick():
#	global upls
#	print('On')
#	upls.ledOn()
#
#
#def onLedOffButtonClick():
#	global upls
#	print('Off')
#	upls.ledOff()
