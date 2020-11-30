from UPLS import HookInfo, LandingGearInfo, WinchInfo, LedInfo
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
		self.update()
	
	def update(self, frequency = 0.0):
		self.var_frequency.set(f'{frequency:.1f}')

	def state(self, state = "disabled"):
		self.ent_frequency["state"] = state


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
		self.update()

	def __setVoltage(self, voltage = 0.0):
		self.ent_voltage_val.set(f'{voltage:.2f}')

	def __setState(self, state = HookInfo.Battery.State.Unknown):
		switcher = { HookInfo.Battery.State.Charging: 		"charging",
					 HookInfo.Battery.State.Discharging: 	"discharging", }
		self.ent_state_val.set(switcher.get(state, "unknown"))

	def update(self, battery = HookInfo.Battery()):
		self.__setVoltage(battery.getVoltage())
		self.__setState(battery.getState())

	def state(self, state = "disabled"):
		self.ent_voltage["state"] = state
		self.ent_state["state"] = state


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
		self.update()

	def __setCurrent(self, current = 0.0):
		self.ent_current_val.set(f'{current:.3f}')

	def __setState(self, state = HookInfo.Battery.State.Unknown):
		switcher = { HookInfo.Latch.State.Open: 	"open",
					 HookInfo.Latch.State.Closed: 	"closed",
					 HookInfo.Latch.State.Opening: 	"opening",
					 HookInfo.Latch.State.Closing: 	"closing", }
		self.ent_state_val.set(switcher.get(state, "unknown"))

	def update(self, latch=HookInfo.Latch()):
		self.__setCurrent(latch.getCurrent())
		self.__setState(latch.getState())

	def state(self, state = "disabled"):
		self.ent_current["state"] = state
		self.ent_state["state"] = state


class HookInfoWidget(Frame):
	def __init__(self, parent):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		# Create all member objects
		self.lbl_title = Label(self, text="Hook", font="bold 14")
		self.lch_latch = LatchWidget(self)
		self.btr_battery = BatteryWidget(self)
		self.lbl_mcu_runtime = Label(self, text="Runtime:")
		self.var_mcu_runtime = StringVar()
		self.ent_mcu_runtime = Entry(self, state="disabled", textvariable=self.var_mcu_runtime, width=6)
		self.lbl_mcu_seconds = Label(self, text="s")
		self.lbl_temperature = Label(self, text="Temperature:")
		self.var_temperature = StringVar()
		self.ent_temperature = Entry(self, state="disabled", textvariable=self.var_temperature, width=6)
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
		self.update()

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

	def update(self, hook_info = HookInfo(), frequency = 0.0):
		self.lch_latch.update(hook_info.getLatchInfo())
		self.btr_battery.update(hook_info.getBatteryInfo())
		self.__setRuntime(hook_info.getMCURuntime())
		self.__setTemperature(hook_info.getTemperature())
		self.__setLost(hook_info.getlostMessages())
		self.__setRetries(hook_info.getAverageRetrie())
		self.ufr_frequency.update(frequency)

	def state(self, state = "disabled"):
		#self.ent_mcu_runtime["state"] = state
		self.ent_temperature["state"] = state
		self.ent_lost["state"] = state
		self.ent_retries["state"] = state
		self.btr_battery.state(state)
		self.lch_latch.state(state)
		self.ufr_frequency.state(state)
	

class LegWidget(Frame):
	def __init__(self, parent, name = "Leg"):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		self.lbl_title   = Label(self, text=name, font="bold")
		self.lbl_status  = Label(self, text="Status:")
		self.var_status  = StringVar()
		self.ent_status  = Entry(self, state="disabled", textvariable=self.var_status, width=8)
		self.lbl_value 	 = Label(self, text="Value:")
		self.var_value 	 = StringVar()
		self.ent_value 	 = Entry(self, state="disabled", textvariable=self.var_value, width=8)
		self.lbl_current = Label(self, text="Current:")
		self.var_current = StringVar()
		self.ent_current = Entry(self, state="disabled", textvariable=self.var_current, width=8)
		self.lbl_A 		 = Label(self, text="A")

		self.lbl_title.grid(column=0, row=0, columnspan=3)
		self.lbl_status.grid(column=0, row=1, sticky="e")
		self.ent_status.grid(column=1, row=1)
		self.lbl_value.grid(column=0, row=2, sticky="e")
		self.ent_value.grid(column=1, row=2)
		self.lbl_current.grid(column=0, row=3, sticky="e")
		self.ent_current.grid(column=1, row=3)
		self.lbl_A.grid(column=2, row=3, sticky="w")

		self.update()

	def __setCurrent(self, current = 0.0):
		self.var_current.set(f'{current:.3f}')

	def __setValue(self, value = 0):
		self.var_value.set(str(value))

	def __setStatus(self, status = LandingGearInfo.Leg.Status.Unknown):
		switcher = { LandingGearInfo.Leg.Status.Open: 		"open",
					 LandingGearInfo.Leg.Status.Closed: 	"closed",
					 LandingGearInfo.Leg.Status.Opening: 	"opening",
					 LandingGearInfo.Leg.Status.Closing: 	"closing", }
		self.var_status.set(switcher.get(status, "unknown"))

	def update(self, leg = LandingGearInfo.Leg()):
		self.__setCurrent(leg.getCurrent())
		self.__setStatus(leg.getStatus())
		self.__setValue(leg.getValue())

	def state(self, state = "disabled"):
		self.ent_status["state"] = state
		self.ent_value["state"] = state
		self.ent_current["state"] = state


class LandingGearInfoWidget(Frame):
	def __init__(self, parent):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)

		self.lbl_title = Label(self, text="Landing Gear", font="bold 14")
		self.leg_front = LegWidget(self, "Front")
		self.leg_rear  = LegWidget(self, "Rear")
		self.ufr_frequency = UpdateFrequencyWidget(self)
		
		self.lbl_title.grid(column=0, row=0, columnspan=2)
		self.leg_front.grid(column=0, row=1)
		self.leg_rear.grid(column=1, row=1)
		self.ufr_frequency.grid(column=0, row=2, columnspan=2, sticky="e")

		self.update()

	def update(self, landing_gear = LandingGearInfo(), frequency = 0.0):
		self.leg_front.update(landing_gear.frontInfo())
		self.leg_rear.update(landing_gear.rearInfo())
		self.ufr_frequency.update(frequency)

	def state(self, state = "disabled"):
		self.leg_front.state(state)
		self.leg_rear.state(state)
		self.ufr_frequency.state(state)


class WinchInfoWidget(Frame):
	def __init__(self, parent):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		self.lbl_title    = Label(self, text="Winch", font="bold 14")
		self.lbl_status   = Label(self, text="Status:")
		self.var_status   = StringVar()
		self.ent_status   = Entry(self, state="disabled", textvariable=self.var_status, width=8)
		self.lbl_position = Label(self, text="Position:")
		self.var_position = StringVar()
		self.ent_position = Entry(self, state="disabled", textvariable=self.var_position, width=8)
		self.lbl_m		  = Label(self, text="m")
		self.lbl_current  = Label(self, text="Current:")
		self.var_current  = StringVar()
		self.ent_current  = Entry(self, state="disabled", textvariable=self.var_current, width=8)
		self.lbl_A 		  = Label(self, text="A")
		self.ufr_frequency = UpdateFrequencyWidget(self)

		self.lbl_title.grid(column=0, row=0, columnspan=3)
		
		self.lbl_status.grid(column=0, row=1, sticky="e")
		self.ent_status.grid(column=1, row=1)
		
		self.lbl_position.grid(column=0, row=2, sticky="e")
		self.ent_position.grid(column=1, row=2)
		self.lbl_m.grid(column=2, row=2, sticky="w")
		
		self.lbl_current.grid(column=0, row=3, sticky="e")
		self.ent_current.grid(column=1, row=3)
		self.lbl_A.grid(column=2, row=3, sticky="w")
		
		self.ufr_frequency.grid(column=0, row=4, columnspan=3, sticky="e")

		self.update()

	def __setCurrent(self, current = 0.0):
		self.var_current.set(f'{current:.3f}')

	def __setPosition(self, position = 0.0):
		self.var_position.set(f'{position:.2f}')

	def __setStatus(self, status = WinchInfo.Status.Unknown):
		switcher = { WinchInfo.Status.Lowering: "lowered",
					 WinchInfo.Status.Lifting: 	"lifting",
					 WinchInfo.Status.Halted: 	"halted",
					 WinchInfo.Status.Lowered: 	"lowered",
					 WinchInfo.Status.Home:		"home", }
		self.var_status.set(switcher.get(status, "unknown"))

	def update(self, winch = WinchInfo(), frequency = 0.0):
		self.__setCurrent(winch.getCurrent())
		self.__setStatus(winch.getStatus())
		self.__setPosition(winch.getPosition())
		self.ufr_frequency.update(frequency)

	def state(self, state = "disabled"):
		self.ent_status["state"] = state
		self.ent_position["state"] = state
		self.ent_current["state"] = state


#class NormalLedModeWidget(Frame):
#	def __inti__(self, parent):
#		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
#		self.lbl_title = Label(self, text="Winch", font="bold")
#		self.lbl_brightness = Label(self, text="Brightness:")
#		self.var_brightness = StringVar()
#		self.ent_brightness = Entry(self, state="disabled", textvariable=self.var_brightness, width=5)
#		
#		self.lbl_title.grid(column=0, row=0, columnspan=2)
#		
#		self.lbl_brightness.grid(column=0, row=1, sticky="e")
#		self.ent_brightness.grid(column=1, row=1)
#
#		self.update()
#
#	def update(self, blinking = LedInfo.Led.Normal()):
#		self.var_brightness.set(blinking.getBrightness())
#
#	def state(self, state = "disabled"):
#		self.ent_brightness["state"] = state
#
#
#class BlinkingLedModeWidget(Frame):
#	def __inti__(self, parent):
#		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
#		self.lbl_title = Label(self, text="Winch", font="bold")
#		self.lbl_onDuration = Label(self, text="On time:")
#		self.var_onDuration = StringVar()
#		self.ent_onDuration = Entry(self, state="disabled", textvariable=self.var_onDuration, width=5)
#		self.lbl_on_ms		= Label(self, text="ms")
#
#		self.lbl_offDuration = Label(self, text="Off time:")
#		self.var_offDuration = StringVar()
#		self.ent_offDuration = Entry(self, state="disabled", textvariable=self.var_offDuration, width=5)
#		self.lbl_off_ms		= Label(self, text="ms")
#
#		self.lbl_title.grid(column=0, row=0, columnspan=3)
#		
#		self.lbl_onDuration.grid(column=0, row=1, sticky="e")
#		self.ent_onDuration.grid(column=1, row=1)
#		self.lbl_on_ms.grid(column=2, row=1, sticky="w")
#
#		self.lbl_offDuration.grid(column=0, row=1, sticky="e")
#		self.ent_offDuration.grid(column=1, row=1)
#		self.lbl_off_ms.grid(column=2, row=1, sticky="w")
#
#		self.update()
#
#	def update(self, blinking = LedInfo.Led.Normal()):
#		self.var_onDuration.set(normal.getBrightness())
#		self.var_offDuration.set(normal.getBrightness())
#
#	def state(self, state = "disabled"):
#		self.ent_brightness["state"] = state

class LedWidget(Frame):
	def __init__(self, parent, name = "<Name>"):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		self.lbl_title = Label(self, text=name, font="bold")
		self.lbl_mode = Label(self, text="Mode:")
		self.var_mode = StringVar()
		self.ent_mode = Entry(self, state="disabled", textvariable = self.var_mode, width=8)

	
	def __setMode(self, mode = LedInfo.Led.Mode.Unknown):
		switcher = { LedInfo.Led.Mode.Normal: "normal",
					 LedInfo.Led.Mode.Pulsing: "pulsing",
					 LedInfo.Led.Mode.FadeInOut: "fade in out",
					 LedInfo.Led.Mode.Blinking: "blinking", }
		self.var_mode.set(switcher.get(mode, "unknown"))


	def update(self, led = LedInfo.Led()):
		self.__setMode(led.getMode())




class LedInfoWidget(Frame):
	def __init__(self, parent):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		self.lbl_title = Label(self, text="Led", font="bold 14")
		