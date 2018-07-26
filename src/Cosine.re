let component = ReasonReact.statelessComponent("Cosine");

let make =
    (
      ~amp,
      ~period,
      ~phase,
      ~offset,
      ~timeDir: int,
      ~visible,
      ~onUpdate,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div>
      <Slider
        min=(-10)
        max=10
        step=0.1
        default=amp
        title="Amplitude"
        onChange=(v => onUpdate(v, period, phase, offset, timeDir, visible))
      />
      <Slider
        min=0
        max=1
        step=0.001
        default=period
        title="Period"
        onChange=(v => onUpdate(amp, v, phase, offset, timeDir, visible))
      />
      <Slider
        min=(-500)
        max=500
        step=1.
        default=phase
        title="Phase"
        onChange=(v => onUpdate(amp, period, -. v, offset, timeDir, visible))
      />
      <Slider
        min=(-2)
        max=2
        step=0.1
        default=offset
        title="Offset"
        onChange=(v => onUpdate(amp, period, phase, v, timeDir, visible))
      />
      <Slider
        min=(-30)
        max=30
        step=1.
        default=(float_of_int(timeDir))
        title="Direction"
        onChange=(
          v => onUpdate(amp, period, phase, offset, int_of_float(v), visible)
        )
      />
      <ToggleButton
        labels=("Show", "Hide")
        state=visible
        onToggle=(b => onUpdate(amp, period, phase, offset, timeDir, b))
      />
    </div>,
};
