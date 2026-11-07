const controlWs = new WebSocket("/controls");

const buttons = {
  direction: {
    up: document.getElementById("up"),
    down: document.getElementById("down"),
    left: document.getElementById("left"),
    right: document.getElementById("right"),
  },
  turn: {
    left: document.getElementById("rot-left"),
    right: document.getElementById("rot-right"),
  },
};

const controls = {
  KeyW: {
    element: buttons.direction.up,
    delta: { x: 0, y: 1, rotation: 0 },
  },
  KeyS: {
    element: buttons.direction.down,
    delta: { x: 0, y: -1, rotation: 0 },
  },
  KeyA: {
    element: buttons.direction.left,
    delta: { x: -1, y: 0, rotation: 0 },
  },
  KeyD: {
    element: buttons.direction.right,
    delta: { x: 1, y: 0, rotation: 0 },
  },
  ArrowLeft: {
    element: buttons.turn.left,
    delta: { x: 0, y: 0, rotation: -1 },
  },
  ArrowRight: {
    element: buttons.turn.right,
    delta: { x: 0, y: 0, rotation: 1 },
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

    direction.x += control.delta.x;
    direction.y += control.delta.y;
    rotation += control.delta.rotation;
  }

  input.direction.x = clamp(direction.x);
  input.direction.y = clamp(direction.y);
  input.rotation = rotation;
}

function updateButtons() {
  for (const [key, control] of Object.entries(controls)) {
    control.element?.classList.toggle("active", pressedKeys.has(key));
  }
}

function sendCommand() {
  controlWs.send(JSON.stringify(input));
}

document.addEventListener("keydown", (event) => {
  if (!controls[event.code]) return;
  if (event.repeat) return;

  event.preventDefault();
  pressedKeys.add(event.code);

  updateInput();
  updateButtons();
  sendCommand();
});

document.addEventListener("keyup", (event) => {
  if (!controls[event.code]) return;
  if (event.repeat) return;

  pressedKeys.delete(event.code);

  updateInput();
  updateButtons();
  sendCommand();
});

window.addEventListener("blur", () => {
  pressedKeys.clear();

  updateInput();
  updateButtons();
  sendCommand();
});
