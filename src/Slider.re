type state = {value: float};
type action =
  | ValueChanged(float);

let component = ReasonReact.reducerComponent("Slider");

let valueFromEvent = evt : float => (
                                      evt
                                      |> ReactEventRe.Form.target
                                      |> ReactDOMRe.domElementToObj
                                    )##value;

let make = (~min, ~max, ~step, ~default, ~title="", ~onChange, _children) => {
  ...component,
  initialState: () => {value: default},
  reducer: (action, _state: state) =>
    switch (action) {
    | ValueChanged(v) => ReasonReact.Update({value: v})
    },
  render: self =>
    <div className="slider">
      <div>
        (
          ReasonReact.string(
            title ++ "= " ++ Js.Float.toString(self.state.value),
          )
        )
      </div>
      <input
        _type="range"
        min
        max=(Js.Float.toString(max))
        step
        value=(Js.Float.toString(self.state.value))
        onChange=(
          evt => {
            let v = valueFromEvent(evt);
            onChange(v);
            self.send(ValueChanged(v));
          }
        )
      />
    </div>,
};
