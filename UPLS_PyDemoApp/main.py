# This Python file uses the following encoding: utf-8
import sys

from UPLS import *
from tkinter import simpledialog, ttk, Button, Toplevel, Label, Frame, Tk, Menu, Entry, Event, EventType, PhotoImage
from custom_widgets import HookInfoWidget, LandingGearInfoWidget, WinchInfoWidget
from custom_widgets import CPUUtilizationWidget, LedInfoWidget, SetNumericParameterWidget
from PIL import Image, ImageTk

hardware_serial_ports = ['/dev/ttyTHS0', '/dev/ttyTHS2', '/dev/ttyV0']

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
		self.lst_AvailablePorts.extend(hardware_serial_ports)
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

		# setup background
		# load = Image.open('/home/lukas/Desktop/domicele.png')
		# background_image = ImageTk.PhotoImage(load)
		# background_label = Label(self.win_Info, image=background_image)
		# background_label.image = background_image
		# background_label.place(x=0, y=0)

		self.win_Info.resizable(False, False)
		self.win_Info.protocol("WM_DELETE_WINDOW", self.__onClosing)
		self.mnb_MenuBar = Menu(self.win_Info)
		self.hki_HookInfo = HookInfoWidget(self.win_Info)
		self.lgi_LandingGearInfo = LandingGearInfoWidget(self.win_Info)
		self.wni_WinchInfo = WinchInfoWidget(self.win_Info)
		self.led_LedInfo = LedInfoWidget(self.win_Info)
		self.cpu_utilization = CPUUtilizationWidget(self.win_Info)
		

		self.hki_HookInfo.grid(column=0, row=0, padx=5, pady=5)
		self.lgi_LandingGearInfo.grid(column=1, row=0, padx=5, pady=5)
		self.wni_WinchInfo.grid(column=2, row=0, padx=5, pady=5)
		self.led_LedInfo.grid(column=0, row=1, columnspan=3, padx=5, pady=5)
		self.cpu_utilization.grid(column=0, row=2, columnspan=3, sticky="e")

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
		
		self.frames = []
		self.buttons = []
		self.labels = []
		self.entries = {}

		self.frames.append(Frame(self.win_Command, relief="ridge", borderwidth=2))
		self.frames[-1].pack(side="left", padx=3, pady=3)

		self.labels.append(Label(self.frames[-1], text="Led"))
		self.labels[-1].pack(side='top', padx=2, pady=2)
		self.buttons.append(Button(self.frames[-1], state="disabled", text="Leds On", command=self.upls.ledsOn))
		self.buttons[-1].pack(side='top', padx=2, pady=2)
		self.buttons.append(Button(self.frames[-1], state="disabled", text="Leds Off", command=self.upls.ledsOff))
		self.buttons[-1].pack(side='top', padx=2, pady=2)

		self.frames.append(Frame(self.win_Command, relief="ridge", borderwidth=2))
		self.frames[-1].pack(side="left", padx=3, pady=3)

		self.labels.append(Label(self.frames[-1], text="Hook"))
		self.labels[-1].grid(column=0, row=0, columnspan=2, padx=2, pady=2)
		self.buttons.append(Button(self.frames[-1], state="disabled", text="Set latch open pulse", command=self.__onOpenPulseSet))
		self.buttons[-1].grid(column=0, row=1, padx=2, pady=2)
		self.buttons.append(Button(self.frames[-1], state="disabled", text="Open latch", command=self.upls.latchOpen))
		self.buttons[-1].grid(column=1, row=1, padx=2, pady=2)
		self.buttons.append(Button(self.frames[-1], state="disabled", text="Set latch close pulse", command=self.__onClosePulseSet))
		self.buttons[-1].grid(column=0, row=2, padx=2, pady=2)
		self.buttons.append(Button(self.frames[-1], state="disabled", text="Close latch", command=self.upls.latchClose))
		self.buttons[-1].grid(column=1, row=2, padx=2, pady=2)
		self.buttons.append(Button(self.frames[-1], state="disabled", text="Shutdown", command=self.upls.hookShutdown))
		self.buttons[-1].grid(column=2, row=1, padx=2, pady=2, rowspan=2, sticky='nesw')

		self.frames.append(Frame(self.win_Command, relief="ridge", borderwidth=2))
		self.frames[-1].pack(side="left", padx=3, pady=3)

		self.labels.append(Label(self.frames[-1], text="Landing Gear"))
		self.labels[-1].pack(side='top', padx=2, pady=2)
		
		self.buttons.append(Button(self.frames[-1], state="disabled", text="Retract", command=self.upls.landingGearRetract))
		self.buttons[-1].pack(side='top', padx=2, pady=2)
		self.buttons.append(Button(self.frames[-1], state="disabled", text="Extract", command=self.upls.landingGearExtract))
		self.buttons[-1].pack(side='top', padx=2, pady=2)

		self.frames.append(Frame(self.win_Command, relief="ridge", borderwidth=2))
		self.frames[-1].pack(side="left", padx=3, pady=3)

		self.labels.append(Label(self.frames[-1], text="Winch"))
		#self.labels[-1].pack(side='top', padx=2, pady=2)
		self.labels[-1].grid(row=0, column=0, columnspan=2, padx=2, pady=2)

		self.frames.append(Frame(self.frames[-1], relief="ridge", borderwidth=2))
		#self.frames[-1].pack(side="left", padx=3, pady=3)
		self.frames[-1].grid(row=1, column=0, padx=3, pady=3)

		self.labels.append(Label(self.frames[-1], text="Manual"))
		self.labels[-1].pack(side='top', padx=2, pady=2)

		entry_validation_test = self.win_Command.register(self.__entryValidate)
		
		def dummy():
			pass

		self.buttons.append(Button(self.frames[-1], state="disabled", text="Up", command=dummy))
		self.buttons[-1].pack(side='top', padx=2, pady=2, fill='x')
		self.up_button = self.buttons[-1]

		self.buttons.append(Button(self.frames[-1], state="disabled", text="Down", command=dummy))
		self.buttons[-1].pack(side='top', padx=2, pady=2, fill='x')
		self.down_button = self.buttons[-1]

		self.entries["ManualControlSpeedEntry"] = Entry(self.frames[-1], state='disabled', 
														width=8, validate='all', 
														validatecommand=(entry_validation_test, '%P'))
		self.entries["ManualControlSpeedEntry"].pack(side='left', padx=2, pady=2)
		self.entries["ManualControlSpeedEntry"].insert('end', '50.0')
		self.labels.append(Label(self.frames[-1], text="%"))
		self.labels[-1].pack(side='left')

		self.up_button_pressed = False
		self.down_button_pressed = False

		self.frames.append(Frame(self.frames[-2], relief="ridge", borderwidth=2))
		#self.frames[-1].pack(side="left", padx=3, pady=3)
		self.frames[-1].grid(row=1, column=1, padx=3, pady=3)
		
		############## WINCH NORMAL MODE COMMANDS #############
		self.labels.append(Label(self.frames[-1], text="Normal"))
		self.labels[-1].pack(side='top', padx=2, pady=2)

		self.buttons.append(Button(self.frames[-1], state="disabled", text="Lift", command=self.upls.winchHome))
		self.buttons[-1].pack(side='top', padx=2, pady=2, fill='x')

		self.buttons.append(Button(self.frames[-1], state="disabled", text="Lower", command=self.__lowerButtonCallback))
		self.buttons[-1].pack(side='top', padx=2, pady=2, fill='x')

		self.buttons.append(Button(self.frames[-1], state="disabled", text="Halt", command=self.upls.winchHalt))
		self.buttons[-1].pack(side='left', padx=2, pady=2, fill='x')

		self.buttons.append(Button(self.frames[-1], state="disabled", text="Resume", command=self.upls.winchResume))
		self.buttons[-1].pack(side='top', padx=2, pady=2, fill='x')

		self.buttons.append(Button(self.frames[-3], state="disabled", text="Manual", command=self.__manualButtonCallback))
		#self.buttons[-1].pack(side='bottom', padx=2, pady=2, fill='x')
		self.buttons[-1].grid(row=2, column=0, columnspan=2, padx=2, pady=2)
		self.manual_button = self.buttons[-1]


	# button callbacks
	def __upButtonCallback(self, event):
		if event.type == EventType.KeyPress or event.type == EventType.ButtonPress:
			self.up_button_pressed = True
			self.up_button['state'] = 'active'
			self.up_button['relief'] = 'sunken'

			speed = 0.0
			try:
				speed = float(self.entries["ManualControlSpeedEntry"].get())
			except:
				pass

			self.__recurentWinchUp(speed)
			
		elif event.type == EventType.KeyRelease or event.type == EventType.ButtonRelease:
			self.up_button_pressed = False
			self.up_button['state'] = 'normal'
			self.up_button['relief'] = 'raised'

	def __downButtonCallback(self, event):
		if event.type == EventType.KeyPress or event.type == EventType.ButtonPress:
			self.down_button_pressed = True
			self.down_button['state'] = 'active'
			self.down_button['relief'] = 'sunken'

			speed = 0.0
			try:
				speed = float(self.entries["ManualControlSpeedEntry"].get())
			except:
				pass

			self.__recurentWinchDown(speed)

		elif event.type == EventType.KeyRelease or event.type == EventType.ButtonRelease:
			self.down_button_pressed = False
			self.down_button['state'] = 'normal'
			self.down_button['relief'] = 'raised'
			return

	def __lowerButtonCallback(self):
		answer = simpledialog.askfloat("Lower", "How much to lower?",
                               parent=self.win_Command,
                               minvalue=0.0, maxvalue=7.0, initialvalue=2.0)
		if isinstance(answer, float):
			self.upls.winchLower(answer)

	def __manualButtonCallback(self):
		if self.upls.winchInfo().getStatus() is WinchInfo.Status.Manual:
			self.upls.winchManualModeDisable()
		else:
			self.upls.winchManualModeEnable()

	def __recurentWinchUp(self, speed):
		if self.up_button_pressed:
			self.upls.winchManualUp(speed, 0.2)
			self.win_Command.after(180, self.__recurentWinchUp, speed)

	def __recurentWinchDown(self, speed):
		if self.down_button_pressed:
			self.upls.winchManualDown(speed, 0.2)
			self.win_Command.after(180, self.__recurentWinchDown, speed)

	# text entry validation. Only digits in range from 0 to 100
	def __entryValidate(self, value):
		val = 0.0
		try:
			val = float(value)
		except:
			if not value: 
				self.entries['ManualControlSpeedEntry'].insert('end', '0') # empty string
			return False
		
		if val >= 0.0 and val <= 350.0:
			return True
		return False

	def __onOpenPulseSet(self):
		answer = simpledialog.askinteger("Set latch open pulse duration", "Enter value (1000-2000us):",
											parent=self.win_Command,
											minvalue=800, maxvalue=2200, 
											initialvalue=self.upls.hookInfo().getLatchInfo().getOpenPulseDuration())
		if answer != None:
			self.upls.latchSetOpenPulseDuration(answer)

	def __onClosePulseSet(self):
		answer = simpledialog.askinteger("Set latch close pulse duration", "Enter value (1000-2000us):",
											parent=self.win_Command,
											minvalue=800, maxvalue=2200, 
											initialvalue=self.upls.hookInfo().getLatchInfo().getClosePulseDuration())
		if answer != None:
			self.upls.latchSetClosePulseDuration(answer)

	def __onClosing(self):
		self.__onDisconnect()
		self.root.destroy()

	def __enableCommands(self, enable = True):
		state = 'disabled'
		if enable:
			state = 'normal'

			self.win_Command.bind('<KeyPress-Up>', self.__upButtonCallback)
			self.win_Command.bind('<KeyRelease-Up>', self.__upButtonCallback)
			self.win_Command.bind('<KeyPress-Down>', self.__downButtonCallback)
			self.win_Command.bind('<KeyRelease-Down>', self.__downButtonCallback)
			self.up_button.bind('<Button-1>', self.__upButtonCallback)
			self.up_button.bind('<ButtonRelease-1>', self.__upButtonCallback)
			self.down_button.bind('<Button-1>', self.__downButtonCallback)
			self.down_button.bind('<ButtonRelease-1>', self.__downButtonCallback)
		
		else:
			self.win_Command.unbind('<KeyPress-Up>')
			self.win_Command.unbind('<KeyRelease-Up>')
			self.win_Command.unbind('<KeyPress-Down>')
			self.win_Command.unbind('<KeyRelease-Down>')
			self.up_button.unbind('<Button-1>')
			self.up_button.unbind('<ButtonRelease-1>')
			self.down_button.unbind('<Button-1>')
			self.down_button.unbind('<ButtonRelease-1>')
		
		for button in self.buttons:
			button["state"] = state

		for entry_key in self.entries:
			self.entries[entry_key]["state"] = state
	
	def __enableWidgets(self, enable = True):
		self.b_ececutePeriodicTasks = enable

		self.__enableCommands(enable)
		
		state = "disabled"
		if enable:
			state = "normal"

		self.hki_HookInfo.state(state)
		self.lgi_LandingGearInfo.state(state)
		self.wni_WinchInfo.state(state)
		self.cpu_utilization.state(state)
		self.led_LedInfo.state(state)

	def __resetWidgets(self):
		self.hki_HookInfo.updateVal()
		self.lgi_LandingGearInfo.updateVal()
		self.wni_WinchInfo.updateVal()
		self.cpu_utilization.updateVal()
		self.led_LedInfo.updateVal()

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
		self.led_LedInfo.updateVal(self.upls.ledInfo(), self.upls.ledInfoUpdateFrequency())
		self.cpu_utilization.updateVal(self.upls.mainControllerInfo().getUtilization())

	def __executePeriodicalTasks(self):
		if self.b_ececutePeriodicTasks:
			self.__periodicalTasks()
		
		self.root.after(100, self.__executePeriodicalTasks)

	def run(self):
		self.root.after(100, self.__executePeriodicalTasks)
		self.root.mainloop()
		


if __name__ == "__main__":
	main_app = MainApp(title = "DEMO")
	main_app.run()
