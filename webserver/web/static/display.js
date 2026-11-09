const joystickDisplay = document.getElementById("joystick-indicator");
const rotationDisplay = document.getElementById("rotation-indicator");

export function updateDirectionDisplay(input) {
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
}

export function updateRotationDisplay(input) {
  const rot = input.rotation;
  const offsetRot = -rot * 50;
  rotationDisplay.style.left = `${50 + offsetRot}%`;
}
