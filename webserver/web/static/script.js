const controlWs = new WebSocket("/controls");

const joystickDisplay = document.getElementById("joystick-indicator");
const rotationDisplay = document.getElementById("rotation-indicator");

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

function updateDisplay() {
  let x = input.direction.x;
  let y = input.direction.y;
  const magnitude = Math.sqrt(x * x + y * y);

  if (magnitude > 1) {
    x /= magnitude;
    y /= magnitude;
  }

  const offsetX = x * 50;
  const offsetY = -y * 50;

  joystickDisplay.style.left = `${50 + offsetX}%`;
  joystickDisplay.style.top = `${50 + offsetY}%`;

  let rot = input.rotation;
  const offsetRot = -rot * 50;
  rotationDisplay.style.left = `${50 + offsetRot}%`;
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
  updateDisplay();
  sendCommand();
});

document.addEventListener("keyup", (event) => {
  if (!controls[event.code]) return;
  if (event.repeat) return;

  pressedKeys.delete(event.code);

  updateInput();
  updateDisplay();
  sendCommand();
});

window.addEventListener("blur", () => {
  pressedKeys.clear();

  updateInput();
  updateDisplay();
  sendCommand();
});
