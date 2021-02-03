from UPLS import HookInfo, LandingGearInfo, WinchInfo, LedInfo
from tkinter import Frame, Label, Entry, StringVar, Spinbox, Button, simpledialog

class SetNumericParameterWidget(Frame):
	def __init__(self, parent, name="Param", onsetaction=0, minvalue=0, maxvalue=1):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		self.label = Label(self, text=name)
		self.spinbox = Spinbox(self, from_=minvalue, to=maxvalue, state="disabled")
		self.button = Button(self, text="Set", state="disabled")
		
		if onsetaction:
			self.button["commnad"] = onsetaction

		self.label.grid(column=0, row=0, sticky="e")
		self.spinbox.grid(column=1, row=0)
		self.button.grid(column=2, row=0)

	def state(self, state="disabled"):
		self.button["state"] = state
		self.spinbox["state"] = state

	def getValue(self):
		return self.spinbox.get()


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
		self.updateVal()
	
	def updateVal(self, frequency = 0.0):
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
		self.updateVal()

	def __setVoltage(self, voltage = 0.0):
		self.ent_voltage_val.set(f'{voltage:.2f}')

	def __setState(self, state = HookInfo.Battery.State.Unknown):
		switcher = { HookInfo.Battery.State.Charging: 		"charging",
					 HookInfo.Battery.State.Discharging: 	"discharging", }
		self.ent_state_val.set(switcher.get(state, "unknown"))

	def updateVal(self, battery = HookInfo.Battery()):
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
		self.lbl_open = Label(self, text="Open pulse duration:")
		self.var_open = StringVar()
		self.ent_open = Entry(self, state="disabled", textvariable=self.var_open, width=8)
		self.lbl_sopen = Label(self, text="s")
		self.lbl_close = Label(self, text="Close pulse duration:")
		self.var_close = StringVar()
		self.ent_close = Entry(self, state="disabled", textvariable=self.var_close, width=8)
		self.lbl_sclose = Label(self, text="s")
		# Set position
		self.lbl_title.grid(column=0, row=0, columnspan=5)
		self.lbl_current.grid(column=0, row=1, sticky="e")
		self.ent_current.grid(column=1, row=1, sticky="e")
		self.lbl_a.grid(column=2, row=1, sticky="w")
		self.lbl_state.grid(column=0, row=2, sticky="e")
		self.ent_state.grid(column=1, row=2, sticky="e")
		self.lbl_open.grid(column=2, row=1, sticky="e")
		self.ent_open.grid(column=3, row=1)
		self.lbl_sopen.grid(column=4, row=1, sticky="w")
		self.lbl_close.grid(column=2, row=2, sticky="e")
		self.ent_close.grid(column=3, row=2)
		self.lbl_sclose.grid(column=4, row=2, sticky="w")
		# Set default values
		self.updateVal()

	def __setCurrent(self, current = 0.0):
		self.ent_current_val.set(f'{current:.3f}')

	def __setState(self, state = HookInfo.Battery.State.Unknown):
		switcher = { HookInfo.Latch.State.Open: 	"open",
					 HookInfo.Latch.State.Closed: 	"closed",
					 HookInfo.Latch.State.Opening: 	"opening",
					 HookInfo.Latch.State.Closing: 	"closing", }
		self.ent_state_val.set(switcher.get(state, "unknown"))

	def updateVal(self, latch=HookInfo.Latch()):
		self.__setCurrent(latch.getCurrent())
		self.__setState(latch.getState())
		self.var_close.set(str(latch.getClosePulseDuration())) 
		self.var_open.set(str(latch.getOpenPulseDuration()))

	def state(self, state = "disabled"):
		self.ent_current["state"] = state
		self.ent_state["state"] = state
		self.ent_close["state"] = state
		self.ent_open["state"] = state


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
		self.updateVal()

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

	def updateVal(self, hook_info = HookInfo(), frequency = 0.0):
		self.lch_latch.updateVal(hook_info.getLatchInfo())
		self.btr_battery.updateVal(hook_info.getBatteryInfo())
		self.__setRuntime(hook_info.getMCURuntime())
		self.__setTemperature(hook_info.getTemperature())
		self.__setLost(hook_info.getlostMessages())
		self.__setRetries(hook_info.getAverageRetrie())
		self.ufr_frequency.updateVal(frequency)

	def state(self, state = "disabled"):
		self.ent_mcu_runtime["state"] = state
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

		self.updateVal()

	def __setCurrent(self, current = 0):
		temp = float(current) / 1000.0
		self.var_current.set(f'{temp:.3f}')

	def __setValue(self, value = 0):
		self.var_value.set(str(value))

	def __setStatus(self, status = LandingGearInfo.Leg.Status.Unknown):
		switcher = { LandingGearInfo.Leg.Status.Up: 			"retracted",
					 LandingGearInfo.Leg.Status.Down: 			"extracted",
					 LandingGearInfo.Leg.Status.InUpTransit: 	"retracting",
					 LandingGearInfo.Leg.Status.InDownTransit: 	"extracting", }
		self.var_status.set(switcher.get(status, "unknown"))

	def updateVal(self, leg = LandingGearInfo.Leg()):
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

		self.updateVal()

	def updateVal(self, landing_gear = LandingGearInfo(), frequency = 0.0):
		self.leg_front.updateVal(landing_gear.frontInfo())
		self.leg_rear.updateVal(landing_gear.rearInfo())
		self.ufr_frequency.updateVal(frequency)

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
		self.lbl_target   = Label(self, text="Target:")
		self.var_target   = StringVar()
		self.ent_target   = Entry(self, state="disabled", textvariable=self.var_target, width=8)
		self.lbl_mt		  = Label(self, text="m")
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

		self.lbl_target.grid(column=0, row=3, sticky="e")
		self.ent_target.grid(column=1, row=3)
		self.lbl_mt.grid(column=2, row=3, sticky="w")
		
		self.lbl_current.grid(column=0, row=4, sticky="e")
		self.ent_current.grid(column=1, row=4)
		self.lbl_A.grid(column=2, row=4, sticky="w")
		
		self.ufr_frequency.grid(column=0, row=5, columnspan=3, sticky="e")

		self.updateVal()

	def __setCurrent(self, current = 0):
		temp = float(current) / 1000.0
		self.var_current.set(f'{temp:.3f}')

	def __setPosition(self, position = 0.0):
		self.var_position.set(f'{position:.2f}')

	def __setTarget(self, target = 0.0):
		self.var_target.set(f'{target:.2f}')

	def __setStatus(self, status = WinchInfo.Status.Unknown):
		switcher = { WinchInfo.Status.Lowering: 			"lowering",
					 WinchInfo.Status.GoingHome: 			"lifting",
					 WinchInfo.Status.Halted: 				"halted",
					 WinchInfo.Status.Lowered: 				"lowered",
					 WinchInfo.Status.Home:					"home",
					 WinchInfo.Status.Manual:				"manual",
					 WinchInfo.Status.Docking: 				"docking" }
		self.var_status.set(switcher.get(status, "unknown"))

	def updateVal(self, winch = WinchInfo(), frequency = 0.0):
		self.__setCurrent(winch.getCurrent())
		self.__setStatus(winch.getStatus())
		self.__setPosition(winch.getPosition())
		self.__setTarget(winch.getTarget())
		self.ufr_frequency.updateVal(frequency)

	def state(self, state = "disabled"):
		self.ent_status["state"] = state
		self.ent_position["state"] = state
		self.ent_target["state"] = state
		self.ent_current["state"] = state
		self.ufr_frequency.state(state)


class CPUUtilizationWidget(Frame):
	def __init__(self, parent):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		self.lbl_label = Label(self, text="CPU Utilization:")
		self.var_util = StringVar()
		self.ent_util = Entry(self, state="disabled", textvariable=self.var_util, width=5)
		self.lbl_prc = Label(self, text="%")

		self.lbl_label.grid(column=0, row=0, sticky="e")
		self.ent_util.grid(column=1, row=0)
		self.lbl_prc.grid(column=2, row=0, sticky="w")

	def updateVal(self, utilization=0.0):
		self.var_util.set(f'{utilization:.1f}')

	def state(self, state = "disabled"):
		self.ent_util["state"] = state


class LedWidget(Frame):
	def __init__(self, parent, name = "<Name>"):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		self.lbl_title = Label(self, text=name, font="bold")
		
		self.lbl_mode = Label(self, text="Mode:")
		self.lbl_enbl = Label(self, text="Enabled:")
		self.lbl_valu = Label(self, text="Value:")

		self.var_mode = StringVar()
		self.var_valu = StringVar()
		self.var_enbl = StringVar()

		self.ent_mode = Entry(self, state="disabled", textvariable = self.var_mode, width=8)
		self.ent_valu = Entry(self, state="disabled", textvariable = self.var_valu, width=8)
		self.ent_enbl = Entry(self, state="disabled", textvariable = self.var_enbl, width=8)

		int_frame = Frame(self, relief="ridge", borderwidth=2)
		lbl_a = Label(int_frame, text="On value:")
		lbl_b = Label(int_frame, text="Off value:")
		lbl_c = Label(int_frame, text="On duration:")
		lbl_d = Label(int_frame, text="Off duration:")
		lbl_e = Label(int_frame, text="ms")
		lbl_f = Label(int_frame, text="ms")
		lbl_g = Label(int_frame, text="Fade-in duration:")
		lbl_h = Label(int_frame, text="Fade-out duration:")
		lbl_i = Label(int_frame, text="ms")
		lbl_j = Label(int_frame, text="ms")

		self.var_onval = StringVar()
		self.var_ofval = StringVar()
		self.var_ondur = StringVar()
		self.var_ofdur = StringVar()
		self.var_fival = StringVar()
		self.var_foval = StringVar()

		self.ent_onval = Entry(int_frame, state="disabled", textvariable=self.var_onval, width=6)
		self.ent_ofval = Entry(int_frame, state="disabled", textvariable=self.var_ofval, width=6)
		self.ent_ondur = Entry(int_frame, state="disabled", textvariable=self.var_ondur, width=6)
		self.ent_ofdur = Entry(int_frame, state="disabled", textvariable=self.var_ofdur, width=6)
		self.ent_fival = Entry(int_frame, state="disabled", textvariable=self.var_fival, width=6)
		self.ent_foval = Entry(int_frame, state="disabled", textvariable=self.var_foval, width=6)

		self.lbl_title.grid(column=0, row=0, columnspan=6)
		self.lbl_mode.grid(column=0, row=1, sticky="e")
		self.ent_mode.grid(column=1, row=1)
		self.lbl_enbl.grid(column=2, row=1, sticky="e")
		self.ent_enbl.grid(column=3, row=1)
		self.lbl_valu.grid(column=4, row=1, sticky="e")
		self.ent_valu.grid(column=5, row=1)
		int_frame.grid(column=0, row=2, columnspan=6, padx=3, pady=3)

		lbl_a.grid(column=0, row=0, sticky="e")
		self.ent_onval.grid(column=1, row=0)
		lbl_c.grid(column=2, row=0, sticky="e")
		self.ent_ondur.grid(column=3, row=0)
		lbl_e.grid(column=4, row=0, sticky="w")
		lbl_g.grid(column=5, row=0, sticky="e")
		self.ent_fival.grid(column=6, row=0)
		lbl_i.grid(column=7, row=0, sticky="w")
		
		lbl_b.grid(column=0, row=1, sticky="e")
		self.ent_ofval.grid(column=1, row=1)
		lbl_d.grid(column=2, row=1, sticky="e")
		self.ent_ofdur.grid(column=3, row=1)
		lbl_f.grid(column=4, row=1, sticky="w")
		lbl_h.grid(column=5, row=1, sticky="e")
		self.ent_foval.grid(column=6, row=1)
		lbl_j.grid(column=7, row=1, sticky="w")

		self.updateVal()
	
	def __setMode(self, mode = LedInfo.Led.Mode.Unknown):
		switcher = { LedInfo.Led.Mode.Normal: "normal",
					 LedInfo.Led.Mode.Pulsing: "pulsing",
					 LedInfo.Led.Mode.Soft: "soft" }
		self.var_mode.set(switcher.get(mode, "unknown"))

	def updateVal(self, led = LedInfo.Led()):
		self.__setMode(led.getMode())
		self.var_valu.set(str(led.getCurrentValue())) 
		
		val = "false"
		if led.getEnabled():
			val = "true"
		self.var_enbl.set(val) 
		
		settings = led.getSettings()
		self.var_onval.set(str(settings.getOnValue()))
		self.var_ofval.set(str(settings.getOffValue()))
		self.var_ondur.set(str(settings.getOnDuration()))
		self.var_ofdur.set(str(settings.getOffDuration()))
		self.var_fival.set(str(settings.getFadeInDuration()))
		self.var_foval.set(str(settings.getFadeOutDuration()))

	def state(self, state="disabled"):
		self.ent_onval["state"] = state
		self.ent_ofval["state"] = state	
		self.ent_ondur["state"] = state	
		self.ent_ofdur["state"] = state	
		self.ent_fival["state"] = state	
		self.ent_foval["state"] = state
		self.ent_mode["state"] = state
		self.ent_valu["state"] = state
		self.ent_enbl["state"] = state

class LedInfoWidget(Frame):
	def __init__(self, parent):
		Frame.__init__(self, parent, relief="ridge", borderwidth=2)
		self.lbl_title = Label(self, text="Led", font="bold 14")
		self.led_front = LedWidget(self, name="Front")
		self.led_rear = LedWidget(self, name="Rear")

		self.ufr_frequency = UpdateFrequencyWidget(self)

		self.lbl_title.grid(column=0, row=0, columnspan=2)
		self.led_front.grid(column=0, row=1)
		self.led_rear.grid(column=1, row=1)
		self.ufr_frequency.grid(column=0, row=2, columnspan=2, sticky="e")

		self.updateVal()

	def updateVal(self, info = LedInfo(), frequency=0.0):
		self.led_front.updateVal(info.frontInfo())
		self.led_rear.updateVal(info.rearInfo())
		self.ufr_frequency.updateVal(frequency)

	def state(self, state="disabled"):
		self.led_front.state(state)
		self.led_rear.state(state)
		self.ufr_frequency.state(state)

'''
class KeyBoundButton(Button):
	def __init__(self, master=None, cnf={}, **kw, key=None, root=None):
		Button.__init__(self, master, cnf, kw)

		if key and root:
			bindKey(key, root)
		

			

	def bindKey(self, key, root):
		root
'''