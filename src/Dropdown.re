let component = ReasonReact.statelessComponent("Dropdown");

let valueFromEvent = evt : string => (
                                       evt
                                       |> ReactEventRe.Form.target
                                       |> ReactDOMRe.domElementToObj
                                     )##value;

let make = (~options, ~onChange, _children) => {
  ...component,
  render: _self =>
    <select onChange=(evt => onChange(valueFromEvent(evt)))>
      (
        options
        |> List.map(t => <option value=t> (ReasonReact.string(t)) </option>)
        |> Array.of_list
        |> ReasonReact.array
      )
    </select>,
};
