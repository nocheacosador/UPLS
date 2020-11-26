from UPLS import *
from tkinter import *
from tkinter import ttk

class BatteryWidget(Frame):
	def __init__(self, parent, default_info="default"):
		Frame.__init__(self, parent, relief="sunken", borderwidth=2)
		# Create all member objects
		self.lbl_title = Label(self, text="Battery")
		self.lbl_voltage = Label(self, text="Voltage:")
		self.ent_voltage_val = StringVar()
		self.ent_voltage = Entry(self, state="readonly", textvariable=self.ent_voltage_val, width=10)
		self.lbl_state = Label(self, text="State:")
		self.ent_state_val = StringVar()
		self.ent_state = Entry(self, state="readonly", textvariable=self.ent_state_val, width=10)
		# Set position
		self.lbl_title.grid(column=0, row=0, columnspan=2)
		self.lbl_voltage.grid(column=0, row=1, sticky=E)
		self.ent_voltage.grid(column=1, row=1, sticky=E)
		self.lbl_state.grid(column=0, row=2, sticky=E)
		self.ent_state.grid(column=1, row=2, sticky=E)
		# Set values
		self.setValues()

	def __setVoltage(self, voltage = 0.0):
		self.ent_voltage_val.set(f'{voltage:.2f}')

	def __setState(self, state = HookInfo.Battery.State.Unknown):
		switcher = { HookInfo.Battery.State.Unknown: "unknown",
					 HookInfo.Battery.State.Charging: "charging",
					 HookInfo.Battery.State.Discharging: "discharging", }
		self.ent_state_val.set(switcher.get(state, "unknown"))

	def setValues(self, battery = HookInfo.Battery()):
		self.__setVoltage(battery.getVoltage())
		self.__setState(battery.getState())
