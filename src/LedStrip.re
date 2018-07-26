type state = {pixels: list(Pixel.t)};
type action =
  | UpdateList;

type transform = (int, int) => float;
type funs = {
  red: list(transform),
  green: list(transform),
  blue: list(transform),
};

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

let sumList = (i, t, fList) =>
  List.fold_left((acc, f) => f(i, t) +. acc, 0., fList);

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
                 r: sumList(i, time, funs.red),
                 g: sumList(i, time, funs.green),
                 b: sumList(i, time, funs.blue),
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
