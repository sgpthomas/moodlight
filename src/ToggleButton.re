let component = ReasonReact.statelessComponent("ToggleButton");

let make = (~labels, ~state=false, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <button onClick=(_evt => onToggle(! state))>
      {
        let (off, on) = labels;
        let str = if (state) {on} else {off};
        ReasonReact.string(str);
      }
    </button>,
};
