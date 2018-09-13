let component = ReasonReact.statelessComponent("Line");

let make = (~slope, ~offset, ~onUpdate, _children) => {
  ...component,
  render: _self =>
    <div>
      <Slider
        min=(-1)
        max=1.
        step=0.01
        default=slope
        title="Slope"
        onChange=(v => onUpdate(v, offset))
      />
      <Slider
        min=(-10)
        max=10.0
        step=0.01
        default=offset
        title="Offset"
        onChange=(v => onUpdate(slope, v))
      />
    </div>,
};
