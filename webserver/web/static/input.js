const eventBus = new EventTarget();

function emit(event, data) {
  eventBus.dispatchEvent(new CustomEvent(event, { detail: data }));
}

export function on(event, callback) {
  eventBus.addEventListener(event, (e) => {
    callback(e.detail);
  });
}

const controls = {
  KeyW: {
    x: 0,
    y: 1,
    rotation: 0,
  },
  KeyS: {
    x: 0,
    y: -1,
    rotation: 0,
  },
  KeyA: {
    x: -1,
    y: 0,
    rotation: 0,
  },
  KeyD: {
    x: 1,
    y: 0,
    rotation: 0,
  },
  ArrowLeft: {
    x: 0,
    y: 0,
    rotation: 1,
  },
  ArrowRight: {
    x: 0,
    y: 0,
    rotation: -1,
  },
};

const input = {
  direction: { x: 0, y: 0 },
  rotation: 0,
};

const pressedKeys = new Set();

const clamp = (value) => Math.max(-1, Math.min(1, value));

function updateInput() {
  const direction = { x: 0, y: 0 };
  let rotation = 0;

  for (const key of pressedKeys) {
    const control = controls[key];
    if (!control) continue;

    direction.x += control.x;
    direction.y += control.y;
    rotation += control.rotation;
  }

  input.direction.x = clamp(direction.x);
  input.direction.y = clamp(direction.y);
  input.rotation = rotation;
}

document.addEventListener("keydown", (event) => {
  if (!controls[event.code]) return;
  if (event.repeat) return;

  event.preventDefault();
  pressedKeys.add(event.code);

  updateInput();
  emit("input:update", input);
});

document.addEventListener("keyup", (event) => {
  if (!controls[event.code]) return;
  if (event.repeat) return;

  pressedKeys.delete(event.code);

  updateInput();
  emit("input:update", input);
});

window.addEventListener("blur", () => {
  pressedKeys.clear();

  updateInput();
  emit("input:update", input);
});
