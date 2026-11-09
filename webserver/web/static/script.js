import { on } from "./input.js";
import { updateDirectionDisplay, updateRotationDisplay } from "./display.js";

const controlWs = new WebSocket("/controls");

on("input:update", (data) => {
  controlWs.send(JSON.stringify(data));
  console.log(
    `Translation: (${data.direction.x}, ${data.direction.y}) Rotation: ${data.rotation}`,
  );

  updateDirectionDisplay(data);
  updateRotationDisplay(data);
});
