type t = {
  id: int,
  size: Pixel.size,
};

let component = ReasonReact.statelessComponent("Point");

let createColor = (y, size: Pixel.size) : ReactDOMRe.style =>
  ReactDOMRe.Style.make(
    ~width=Pixel.string_of_px(size.x),
    ~height=
      Pixel.string_of_px(size.y - int_of_float(y *. float_of_int(size.y))),
    (),
  );

let make = (~size, ~y: float, _children) => {
  ...component,
  render: _self => <div className="point" style=(createColor(y, size)) />,
};
