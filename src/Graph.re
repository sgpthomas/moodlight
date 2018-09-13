type state = {points: list(Point.t)};
type action =
  | UpdateList;

type transform = (int, int) => (float, float, float);
type funs = list(transform);

let component = ReasonReact.reducerComponent("Graph");

let idRef = ref(-1);
let nextPixel = size => {
  idRef := idRef^ + 1;
  {Point.id: idRef^, Point.size};
};

let rec makePoints = (num, size) =>
  switch (num) {
  | 0 => []
  | x when x < 0 => failwith("Need a positive size")
  | _ => [nextPixel(size), ...makePoints(num - 1, size)]
  };

let test = (i, t) => float_of_int((i + t) mod 255) /. 255.;

let sumList = (i, t, fList: list(transform)) =>
  List.fold_left(
    (acc, f) => {
      let (r0, g0, b0) = f(i, t);
      let (rT, gT, bT) = acc;
      (r0 +. rT, g0 +. gT, b0 +. bT);
    },
    (0., 0., 0.),
    fList,
  );

let make = (~num, ~size, _children) => {
  ...component,
  initialState: () => {points: makePoints(num, size)},
  reducer: (action: action, _state: state) =>
    switch (action) {
    | UpdateList => ReasonReact.NoUpdate
    },
  willReceiveProps: _self => {
    idRef := (-1);
    {points: makePoints(num, size)};
  },
  render: self =>
    <div
      id="graph"
      style=(ReactDOMRe.Style.make(~height=Pixel.string_of_px(size.y), ()))>
      (
        self.state.points
        |> List.map((point: Point.t) =>
             <Point
               key=(string_of_int(point.id))
               size=point.size
               y=(sin(0.05 *. float_of_int(point.id)))
             />
           )
        |> Array.of_list
        |> ReasonReact.array
      )
    </div>,
};
