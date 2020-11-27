from UPLS import HookInfo
from tkinter import Frame, Label, Entry, StringVar


class UpdateFrequencyWidget(Frame):
	def __init__(self, parent):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		# Create all member objects
		self.lbl_frequency = Label(self, text="Update frequency:")
		self.var_frequency = StringVar()
		self.ent_frequency = Entry(self, state="disabled", textvariable=self.var_frequency, width=5)
		self.lbl_hertz = Label(self, text="Hz")
		# Set position
		self.lbl_frequency.grid(column=0, row=0, sticky="e")
		self.ent_frequency.grid(column=1, row=0, sticky="e")
		self.lbl_hertz.grid(column=2, row=0, sticky="w")
		# Set default values
		self.setValue()
	
	def setValue(self, frequency = 0.0):
		self.var_frequency.set(f'{frequency:.1f}')


class BatteryWidget(Frame):
	def __init__(self, parent):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		# Create all member objects
		self.lbl_title = Label(self, text="Battery", font="bold")
		self.lbl_voltage = Label(self, text="Voltage:")
		self.ent_voltage_val = StringVar()
		self.ent_voltage = Entry(self, state="disabled", textvariable=self.ent_voltage_val, width=10)
		self.lbl_v = Label(self, text="V")
		self.lbl_state = Label(self, text="State:")
		self.ent_state_val = StringVar()
		self.ent_state = Entry(self, state="disabled", textvariable=self.ent_state_val, width=10)
		# Set position
		self.lbl_title.grid(column=0, row=0, columnspan=3, sticky="ew")
		self.lbl_voltage.grid(column=0, row=1, sticky="e")
		self.ent_voltage.grid(column=1, row=1,)
		self.lbl_v.grid(column=2, row=1, sticky="w")
		self.lbl_state.grid(column=0, row=2, sticky="e")
		self.ent_state.grid(column=1, row=2)
		# Set default values
		self.setValues()

	def __setVoltage(self, voltage = 0.0):
		self.ent_voltage_val.set(f'{voltage:.2f}')

	def __setState(self, state = HookInfo.Battery.State.Unknown):
		switcher = { HookInfo.Battery.State.Charging: 		"charging",
					 HookInfo.Battery.State.Discharging: 	"discharging", }
		self.ent_state_val.set(switcher.get(state, "unknown"))

	def setValues(self, battery = HookInfo.Battery()):
		self.__setVoltage(battery.getVoltage())
		self.__setState(battery.getState())


class LatchWidget(Frame):
	def __init__(self, parent):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		# Create all member objects
		self.lbl_title = Label(self, text="Latch", font="bold")
		self.lbl_current = Label(self, text="Current:")
		self.ent_current_val = StringVar()
		self.ent_current = Entry(self, state="disabled", textvariable=self.ent_current_val, width=10)
		self.lbl_a = Label(self, text="A")
		self.lbl_state = Label(self, text="State:")
		self.ent_state_val = StringVar()
		self.ent_state = Entry(self, state="disabled", textvariable=self.ent_state_val, width=10)
		# Set position
		self.lbl_title.grid(column=0, row=0, columnspan=3)
		self.lbl_current.grid(column=0, row=1, sticky="e")
		self.ent_current.grid(column=1, row=1, sticky="e")
		self.lbl_a.grid(column=2, row=1, sticky="W")
		self.lbl_state.grid(column=0, row=2, sticky="e")
		self.ent_state.grid(column=1, row=2, sticky="e")
		# Set default values
		self.setValues()

	def __setCurrent(self, current = 0.0):
		self.ent_current_val.set(f'{current:.2f}')

	def __setState(self, state = HookInfo.Battery.State.Unknown):
		switcher = { HookInfo.Latch.State.Open: 	"open",
					 HookInfo.Latch.State.Closed: 	"closed",
					 HookInfo.Latch.State.Opening: 	"opening",
					 HookInfo.Latch.State.Closing: 	"closing", }
		self.ent_state_val.set(switcher.get(state, "unknown"))

	def setValues(self, latch=HookInfo.Latch()):
		self.__setCurrent(latch.getCurrent())
		self.__setState(latch.getState())


class HookInfoWidget(Frame):
	def __init__(self, parent):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		# Create all member objects
		self.lbl_title = Label(self, text="Hook", font="bold 14")
		self.lch_latch = LatchWidget(self)
		self.btr_battery = BatteryWidget(self)
		self.lbl_mcu_runtime = Label(self, text="Runtime:")
		self.var_mcu_runtime = StringVar()
		self.ent_mcu_runtime = Entry(self, state="disabled", textvariable=self.var_mcu_runtime, width=5)
		self.lbl_mcu_seconds = Label(self, text="s")
		self.lbl_temperature = Label(self, text="Temperature:")
		self.var_temperature = StringVar()
		self.ent_temperature = Entry(self, state="disabled", textvariable=self.var_temperature, width=5)
		self.lbl_degrees = Label(self, text="°C")
		self.lbl_lost = Label(self, text="Lost:")
		self.var_lost = StringVar()
		self.ent_lost = Entry(self, state="disabled", textvariable=self.var_lost, width=5)
		self.lbl_retries = Label(self, text="Retries:")
		self.var_retries = StringVar()
		self.ent_retries = Entry(self, state="disabled", textvariable=self.var_retries, width=5)
		self.ufr_frequency = UpdateFrequencyWidget(self)
		# Set position
		self.lbl_title.grid(column=0, row=0, columnspan=5)
		self.lch_latch.grid(column=0, row=1, columnspan=3)
		self.btr_battery.grid(column=3, row=1, columnspan=2)
		self.lbl_mcu_runtime.grid(column=0, row=2, sticky="e")
		self.ent_mcu_runtime.grid(column=1, row=2, sticky="e")
		self.lbl_mcu_seconds.grid(column=2, row=2, sticky="w")
		self.lbl_retries.grid(column=3, row=2, sticky="e")
		self.ent_retries.grid(column=4, row=2)
		self.lbl_temperature.grid(column=0, row=3, sticky="e")
		self.ent_temperature.grid(column=1, row=3, sticky="e")
		self.lbl_degrees.grid(column=2, row=3, sticky="w")
		self.lbl_lost.grid(column=3, row=3, sticky="e")
		self.ent_lost.grid(column=4, row=3)
		self.ufr_frequency.grid(column=0, row=4, columnspan=5, sticky="e")
		# Set default values
		self.setValues()

	def __setRuntime(self, runtime = 0.0):
		if runtime < 100.0:
			self.var_mcu_runtime.set(f'{runtime:.1f}')
		else:
			self.var_mcu_runtime.set(f'{runtime:.0f}')

	def __setTemperature(self, temperature = 0.0):
		self.var_temperature.set(f'{temperature:.1f}')

	def __setRetries(self, retries = 0.0):
		self.var_retries.set(f'{retries:.1f}')

	def __setLost(self, lost = 0):
		self.var_lost.set(str(lost))

	def setValues(self, hook_info = HookInfo(), frequency = 0.0):
		self.lch_latch = hook_info.getBatteryInfo()
		self.btr_battery = hook_info.getLatchInfo()
		self.__setRuntime(hook_info.getMCURuntime())
		self.__setTemperature(hook_info.getTemperature())
		self.__setLost(hook_info.getlostMessages())
		self.__setRetries(hook_info.getAverageRetrie())
		self.ufr_frequency.setValue(frequency)

		