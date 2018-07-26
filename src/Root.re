type colorState = {
  handler: LedCanvas.handler,
  period: float,
  off: int,
  direction: int,
};
type colorFunction =
  | Cos(float, float, float, float, int); /* A cos (b x + c) + d */
type allFuns = {
  red: list((colorFunction, bool)),
  green: list((colorFunction, bool)),
  blue: list((colorFunction, bool)),
};
type state = {
  pixelCount: int,
  pixelSize: Pixel.size,
  clockSpeed: int,
  time: int,
  timerId: ref(option(Js.Global.intervalId)),
  funs: allFuns,
  running: bool,
};
type action =
  | Tick
  | SetRunning(bool)
  | ResetTime
  | UpdateCount(int)
  | UpdateSize(int, int)
  | UpdateClockSpeed(int)
  | NewRed
  | UpdateRed(int, colorFunction, bool)
  | DeleteRed
  | NewGreen
  | UpdateGreen(int, colorFunction, bool)
  | DeleteGreen
  | NewBlue
  | UpdateBlue(int, colorFunction, bool)
  | DeleteBlue;

let component = ReasonReact.reducerComponent("Root");

let floatify = f => Js.Float.fromString(Js.Float.toString(f));

let pi = Js.Math._PI;
let unwrap_colorFunction = ((colorF, b)) =>
  if (b) {
    switch (colorF) {
    | Cos(amp, period, phase, offset, timeDir) => (
        (i, t) =>
          amp
          *. cos(
               2.
               *. pi
               *. period
               *. (float_of_int(i + t * (- timeDir)) +. floatify(phase)),
             )
          +. floatify(offset)
      )
    };
  } else {
    (_i, _t) => 0.;
  };

let attachNewTimer = (state, send) =>
  switch (state.timerId^) {
  | Some(_) => ()
  | None =>
    if (state.clockSpeed > 0) {
      let timerId =
        Js.Global.setInterval(() => send(Tick), state.clockSpeed);
      send(SetRunning(true));
      state.timerId := Some(timerId);
    } else {
      state.timerId := None;
    }
  };

let removeTimer = (state, send) =>
  switch (state.timerId^) {
  | Some(id) =>
    Js.Global.clearInterval(id);
    send(SetRunning(false));
    state.timerId := None;
  | None => ()
  };

let default = {
  pixelCount: 300,
  pixelSize: {
    x: 3,
    y: 60,
  },
  clockSpeed: 50,
  time: 0,
  timerId: ref(None),
  funs: {
    red: [],
    green: [],
    blue: [],
  },
  running: false,
};

let make = _children => {
  ...component,
  initialState: () => default,
  reducer: (action, state: state) =>
    switch (action) {
    | Tick => ReasonReact.Update({...state, time: state.time + 1})
    | SetRunning(r) => ReasonReact.Update({...state, running: r})
    | ResetTime => ReasonReact.Update({...state, time: 0})
    | UpdateCount(i) => ReasonReact.Update({...state, pixelCount: i})
    | UpdateSize(x, y) => ReasonReact.Update({
                             ...state,
                             pixelSize: {
                               x,
                               y,
                             },
                           })
    | UpdateClockSpeed(i) => ReasonReact.Update({...state, clockSpeed: i})
    | NewRed =>
      ReasonReact.Update({
        ...state,
        funs: {
          ...state.funs,
          red:
            List.append(
              state.funs.red,
              [(Cos(0.5, 0.1, 0., 0.5, 3), true)],
            ),
        },
      })
    | UpdateRed(n, colF, vis) =>
      ReasonReact.Update({
        ...state,
        funs: {
          ...state.funs,
          red:
            List.mapi(
              (i, x) =>
                if (i == n) {
                  (colF, vis);
                } else {
                  x;
                },
              state.funs.red,
            ),
        },
      })
    | DeleteRed =>
      ReasonReact.Update({
        ...state,
        funs: {
          ...state.funs,
          red:
            switch (List.rev(state.funs.red)) {
            | [_hd, ...tl] => List.rev(tl)
            | [] => []
            },
        },
      })
    | NewGreen =>
      ReasonReact.Update({
        ...state,
        funs: {
          ...state.funs,
          green:
            List.append(
              state.funs.green,
              [(Cos(0.5, 0.1, 0., 0.5, 3), true)],
            ),
        },
      })
    | UpdateGreen(n, colF, vis) =>
      ReasonReact.Update({
        ...state,
        funs: {
          ...state.funs,
          green:
            List.mapi(
              (i, x) =>
                if (i == n) {
                  (colF, vis);
                } else {
                  x;
                },
              state.funs.green,
            ),
        },
      })
    | DeleteGreen =>
      ReasonReact.Update({
        ...state,
        funs: {
          ...state.funs,
          green:
            switch (List.rev(state.funs.green)) {
            | [_hd, ...tl] => List.rev(tl)
            | [] => []
            },
        },
      })
    | NewBlue =>
      ReasonReact.Update({
        ...state,
        funs: {
          ...state.funs,
          blue:
            List.append(
              state.funs.blue,
              [(Cos(0.5, 0.1, 0., 0.5, 3), true)],
            ),
        },
      })
    | UpdateBlue(n, colF, vis) =>
      ReasonReact.Update({
        ...state,
        funs: {
          ...state.funs,
          blue:
            List.mapi(
              (i, x) =>
                if (i == n) {
                  (colF, vis);
                } else {
                  x;
                },
              state.funs.blue,
            ),
        },
      })
    | DeleteBlue =>
      ReasonReact.Update({
        ...state,
        funs: {
          ...state.funs,
          blue:
            switch (List.rev(state.funs.blue)) {
            | [_hd, ...tl] => List.rev(tl)
            | [] => []
            },
        },
      })
    },
  render: self =>
    <div id="root">
      <div className="row">
        <div className="col">
          <h3> (ReasonReact.string("Strip Controls")) </h3>
          <Slider
            min=1
            max=50
            step=1.
            default=(float_of_int(default.pixelSize.x))
            title="X"
            onChange=(
              v =>
                self.send(
                  UpdateSize(int_of_float(v), self.state.pixelSize.y),
                )
            )
          />
          <Slider
            min=1
            max=500
            step=1.
            default=(float_of_int(default.pixelSize.y))
            title="Y"
            onChange=(
              v =>
                self.send(
                  UpdateSize(self.state.pixelSize.x, int_of_float(v)),
                )
            )
          />
          <Slider
            min=1
            max=500
            step=1.
            default=(float_of_int(default.pixelCount))
            title="Count"
            onChange=(v => self.send(UpdateCount(int_of_float(v))))
          />
          <Slider
            min=1
            max=200
            step=1.
            default=(float_of_int(default.clockSpeed))
            title="Speed"
            onChange=(v => self.send(UpdateClockSpeed(int_of_float(v))))
          />
          (ReasonReact.string("Time: " ++ string_of_int(self.state.time)))
          <div>
            <button
              onMouseDown=(_evt => attachNewTimer(self.state, self.send))
              onMouseUp=(_evt => removeTimer(self.state, self.send))>
              (ReasonReact.string("Tick!"))
            </button>
            <ToggleButton
              labels=("Start", "Stop")
              state=self.state.running
              onToggle=(
                b =>
                  if (b) {
                    attachNewTimer(self.state, self.send);
                  } else {
                    removeTimer(self.state, self.send);
                  }
              )
            />
            <button onClick=(_evt => self.send(ResetTime))>
              (ReasonReact.string("Reset"))
            </button>
          </div>
        </div>
      </div>
      <LedStrip
        num=self.state.pixelCount
        size=self.state.pixelSize
        time=self.state.time
        funs={
          LedStrip.red: List.map(unwrap_colorFunction, self.state.funs.red),
          LedStrip.green:
            List.map(unwrap_colorFunction, self.state.funs.green),
          LedStrip.blue: List.map(unwrap_colorFunction, self.state.funs.blue),
        }
      />
      <div className="col">
        <button onClick=(_evt => self.send(NewRed))>
          (ReasonReact.string("New Red"))
        </button>
        <button onClick=(_evt => self.send(DeleteRed))>
          (ReasonReact.string("Delete Red"))
        </button>
        (
          self.state.funs.red
          |> List.mapi((i, (colF, visible)) =>
               switch (colF) {
               | Cos(amp, period, phase, offset, timeDir) =>
                 <div>
                   (ReasonReact.string(string_of_int(i)))
                   <Cosine
                     key=(string_of_int(i))
                     amp
                     period
                     phase
                     offset
                     timeDir
                     visible
                     onUpdate=(
                       (a, p, ph, off, td, vis) =>
                         self.send(
                           UpdateRed(i, Cos(a, p, ph, off, td), vis),
                         )
                     )
                   />
                 </div>
               }
             )
          |> Array.of_list
          |> ReasonReact.array
        )
      </div>
      <div className="col">
        <button onClick=(_evt => self.send(NewGreen))>
          (ReasonReact.string("New Green"))
        </button>
        <button onClick=(_evt => self.send(DeleteGreen))>
          (ReasonReact.string("Delete Green"))
        </button>
        (
          self.state.funs.green
          |> List.mapi((i, (colF, visible)) =>
               switch (colF) {
               | Cos(amp, period, phase, offset, timeDir) =>
                 <div>
                   (ReasonReact.string(string_of_int(i)))
                   <Cosine
                     key=(string_of_int(i))
                     amp
                     period
                     phase
                     offset
                     timeDir
                     visible
                     onUpdate=(
                       (a, p, ph, off, td, vis) =>
                         self.send(
                           UpdateGreen(i, Cos(a, p, ph, off, td), vis),
                         )
                     )
                   />
                 </div>
               }
             )
          |> Array.of_list
          |> ReasonReact.array
        )
      </div>
      <div className="col">
        <button onClick=(_evt => self.send(NewBlue))>
          (ReasonReact.string("New Blue"))
        </button>
        <button onClick=(_evt => self.send(DeleteBlue))>
          (ReasonReact.string("Delete Blue"))
        </button>
        (
          self.state.funs.blue
          |> List.mapi((i, (colF, visible)) =>
               switch (colF) {
               | Cos(amp, period, phase, offset, timeDir) =>
                 <div>
                   (ReasonReact.string(string_of_int(i)))
                   <Cosine
                     key=(string_of_int(i))
                     amp
                     period
                     phase
                     offset
                     timeDir
                     visible
                     onUpdate=(
                       (a, p, ph, off, td, vis) =>
                         self.send(
                           UpdateBlue(i, Cos(a, p, ph, off, td), vis),
                         )
                     )
                   />
                 </div>
               }
             )
          |> Array.of_list
          |> ReasonReact.array
        )
      </div>
    </div>,
};
