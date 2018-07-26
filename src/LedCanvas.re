type state = {
  timerId: ref(option(Js.Global.intervalId)),
  pixels: list(Pixel.t),
  time: int,
};
type action =
  | UpdateList
  | Tick;

type handler = (int, int) => float;

let component = ReasonReact.reducerComponent("LedCanvas");

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

let attachNewTimer = (state, send, clockSpeed) =>
  if (clockSpeed > 0) {
    let timerId = Js.Global.setInterval(() => send(Tick), clockSpeed);
    state.timerId := Some(timerId);
  } else {
    state.timerId := None;
  };

let make = (~num, ~size, ~clockSpeed, ~red, ~green, ~blue, _children) => {
  ...component,
  initialState: () => {
    timerId: ref(None),
    pixels: makePixels(num, size),
    time: 0,
  },
  reducer: (action, state: state) =>
    switch (action) {
    | UpdateList =>
      ReasonReact.Update({...state, pixels: makePixels(num, size)})
    | Tick => ReasonReact.Update({...state, time: state.time + 1})
    },
  didMount: self => attachNewTimer(self.state, self.send, clockSpeed),
  willReceiveProps: self => {...self.state, pixels: makePixels(num, size)},
  didUpdate: ({oldSelf, newSelf}) => {
    switch (oldSelf.state.timerId^) {
    | Some(id) => Js.Global.clearInterval(id)
    | None => ()
    };
    attachNewTimer(newSelf.state, newSelf.send, clockSpeed);
  },
  render: self =>
    <div id="ledstrip">
      (
        List.mapi(
          (i, pix: Pixel.t) => {
            ...pix,
            color: {
              r: red(i, self.state.time),
              g: green(i, self.state.time),
              b: blue(i, self.state.time),
            },
          },
          self.state.pixels,
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
