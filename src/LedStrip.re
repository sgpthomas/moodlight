type state = {pixels: list(Pixel.t)};
type action =
  | UpdateList;

type transform = (int, int) => (float, float, float);
type funs = list(transform);

let component = ReasonReact.reducerComponent("LedStrip");

let idRef = ref(-1);
let nextPixel = size => {
  idRef := idRef^ + 1;
  {
    Pixel.id: idRef^,
    Pixel.size,
    Pixel.color: {
      r: 0.,
      g: 0.,
      b: 0.,
    },
  };
};

let rec makePixels = (num, size) =>
  switch (num) {
  | 0 => []
  | x when x < 0 => failwith("Need a positive size")
  | _ => [nextPixel(size), ...makePixels(num - 1, size)]
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

let make = (~num, ~size, ~time, ~funs, _children) => {
  ...component,
  initialState: () => {pixels: makePixels(num, size)},
  reducer: (action: action, _state: state) =>
    switch (action) {
    | UpdateList => ReasonReact.NoUpdate
    },
  willReceiveProps: _self => {
    idRef := (-1);
    {pixels: makePixels(num, size)};
  },
  render: self =>
    <div id="ledstrip">
      (
        self.state.pixels
        |> List.mapi((i, pix: Pixel.t) =>
             {
               ...pix,
               color: {
                 let (r, g, b) = sumList(i, time, funs);
                 {r, g, b};
               },
             }
           )
        |> List.map((pixel: Pixel.t) =>
             <Pixel
               key=(string_of_int(pixel.id))
               size=pixel.size
               color=pixel.color
             />
           )
        |> Array.of_list
        |> ReasonReact.array
      )
    </div>,
};
