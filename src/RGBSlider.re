let component = ReasonReact.statelessComponent("RGBSlider");

let make = (~red, ~green, ~blue, ~onUpdate, _children) => {
  ...component,
  render: _self =>
    <div>
      <Slider
        min=0
        max=1.
        step=0.01
        default=red
        title="Red"
        onChange=(v => onUpdate(v, green, blue))
      />
      <Slider
        min=0
        max=1.
        step=0.01
        default=green
        title="Green"
        onChange=(v => onUpdate(red, v, blue))
      />
      <Slider
        min=0
        max=1.
        step=0.01
        default=blue
        title="Blue"
        onChange=(v => onUpdate(red, green, v))
      />
    </div>,
};
