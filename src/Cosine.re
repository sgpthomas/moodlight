let component = ReasonReact.statelessComponent("Cosine");

let make = (~amp, ~period, ~phase, ~offset, ~timeDir, ~onUpdate, _children) => {
  ...component,
  render: _self =>
    <div>
      <Slider
        min=(-10)
        max=10.0
        step=0.01
        default=amp
        title="Amplitude"
        onChange=(v => onUpdate(v, period, phase, offset, timeDir))
      />
      <Slider
        min=0
        max=0.4
        step=0.001
        default=period
        title="Period"
        onChange=(v => onUpdate(amp, v, phase, offset, timeDir))
      />
      <Slider
        min=(-500)
        max=500.
        step=1.
        default=phase
        title="Phase"
        onChange=(v => onUpdate(amp, period, -. v, offset, timeDir))
      />
      <Slider
        min=(-2)
        max=2.
        step=0.1
        default=offset
        title="Offset"
        onChange=(v => onUpdate(amp, period, phase, v, timeDir))
      />
      <Slider
        min=(-30)
        max=30.
        step=0.1
        default=timeDir
        title="Direction"
        onChange=(v => onUpdate(amp, period, phase, offset, v))
      />
    </div>,
};
