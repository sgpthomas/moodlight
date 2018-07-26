type px = int;
type color = {
  r: float,
  g: float,
  b: float,
};
type size = {
  x: px,
  y: px,
};

type t = {
  id: int,
  size,
  color,
};

let component = ReasonReact.statelessComponent("Pixel");

let string_of_px = (i: int) => Printf.sprintf("%dpx", i);
let string_of_color = ({r, g, b}) =>
  Printf.sprintf(
    "rgb(%d, %d, %d)",
    int_of_float(r *. 255.),
    int_of_float(g *. 255.),
    int_of_float(b *. 255.),
  );

let createColor = (col: color, size: size) : ReactDOMRe.style =>
  ReactDOMRe.Style.make(
    ~backgroundColor=string_of_color(col),
    ~width=string_of_px(size.x),
    ~height=string_of_px(size.y),
    (),
  );

let make = (~size, ~color, _children) => {
  ...component,
  render: _self => <div className="pixel" style=(createColor(color, size)) />,
};
