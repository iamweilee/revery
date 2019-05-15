open Revery;
open Revery.Math;
open Revery.UI;

let logo = {
  let component = React.component("logo");

  (~children as _: list(React.syntheticElement), ()) =>
    component(hooks => {
      let (logoOpacity, setOpacity, hooks) = Hooks.state(1.0, hooks);

      let (rotation, hooks) =
        Hooks.animation(
          Animated.floatValue(0.),
          {
            toValue: 6.28,
            duration: Seconds(8.),
            delay: Seconds(1.0),
            repeat: true,
            easing: Animated.linear,
            direction: `Normal,
          },
          hooks,
        );

      let (rotationY, hooks) =
        Hooks.animation(
          Animated.floatValue(0.),
          {
            toValue: 6.28,
            duration: Seconds(4.),
            delay: Seconds(0.5),
            repeat: true,
            easing: Animated.linear,
            direction: `Normal,
          },
          hooks,
        );

      let onMouseDown = _ => setOpacity(0.5);

      let onMouseUp = _ => setOpacity(1.0);

      (
        hooks,
        <View onMouseDown onMouseUp>
          <Image
            src="outrun-logo.png"
            style=Style.[
              width(512),
              height(256),
              opacity(logoOpacity),
              transform([
                Transform.RotateY(Angle.from_radians(rotationY)),
                Transform.RotateX(Angle.from_radians(rotation)),
              ]),
            ]
          />
        </View>,
      );
    });
};

let animatedText = {
  let component = React.component("AnimatedText");

  (~children as _: list(React.syntheticElement), ~text: string, ~delay: float, ()) =>
    component(hooks => {
      let (animatedOpacity, hooks) =
        Hooks.animation(
          Animated.floatValue(0.),
          {
            toValue: 1.0,
            duration: Seconds(1.),
            delay: Seconds(delay),
            repeat: false,
            easing: Animated.linear,
            direction: `Normal,
          },
          hooks,
        );

      let (translate, hooks) =
        Hooks.animation(
          Animated.floatValue(50.),
          {
            toValue: 0.,
            duration: Seconds(0.5),
            delay: Seconds(delay),
            repeat: false,
            easing: Animated.linear,
            direction: `Normal,
          },
          hooks,
        );

      let textHeaderStyle =
        Style.[
          color(Colors.white),
          fontFamily("Roboto-Regular.ttf"),
          fontSize(24),
          marginHorizontal(8),
          opacity(animatedOpacity),
          transform([Transform.TranslateY(translate)]),
        ];

      (hooks, <Text style=textHeaderStyle text />);
    });
};

let render = () =>
  <View
    style=Style.[
      position(`Absolute),
      justifyContent(`Center),
      alignItems(`Center),
      bottom(0),
      top(0),
      left(0),
      right(0),
    ]>
    <View
      ref={r =>
        print_endline(
          "View internal id:" ++ string_of_int(r#getInternalId()),
        )
      }
      style=Style.[flexDirection(`Row), alignItems(`FlexEnd)]>
      <animatedText delay=0.0 text="Welcome" />
      <animatedText delay=0.5 text="to" />
      <animatedText delay=1. text="Revery" />
    </View>
    <logo />
  </View>;
