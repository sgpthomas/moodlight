type colorFunction =
  | Nothing
  | Cos(float, float, float, float, float) /* A cos (b x + c) + d */
  | Line(float, float) /* a x + b */
  | Custom(string, list(colorFunction));

type t = {
  id: int,
  name: string,
  f: colorFunction,
  visible: bool,
  color: (float, float, float),
};

let compare = (a: t, b: t) : int => compare(a.id, b.id);
