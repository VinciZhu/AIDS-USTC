<script setup lang="ts">
import { ref, getCurrentInstance, onMounted } from "vue"
import Matter from "matter-js"
const {
  Events,
  Engine,
  Render,
  Body,
  Bodies,
  Runner,
  Common,
  Composite,
} = Matter
defineProps<{}>()
defineEmits<{}>()
const instance = getCurrentInstance()
let canvas, engine, world, render, runner, composite
function newRenderBodies(render, bodies, context) {
  let c = context,
    engine = render.engine,
    options = render.options,
    showInternalEdges = options.showInternalEdges || !options.wireframes,
    body,
    part,
    i,
    k

  for (i = 0; i < bodies.length; i++) {
    body = bodies[i]

    if (!body.render.visible) continue

    // handle compound parts
    for (k = body.parts.length > 1 ? 1 : 0; k < body.parts.length; k++) {
      part = body.parts[k]

      if (!part.render.visible) continue

      if (options.showSleeping && body.isSleeping) {
        c.globalAlpha = 0.5 * part.render.opacity
      } else if (part.render.opacity !== 1) {
        c.globalAlpha = part.render.opacity
      }

      if (
        part.render.sprite &&
        part.render.sprite.texture &&
        !options.wireframes
      ) {
        // part sprite
        const sprite = part.render.sprite,
          texture = Render._getTexture(render, sprite.texture)

        c.translate(part.position.x, part.position.y)
        c.rotate(part.angle)

        c.drawImage(
          texture,
          texture.width * -sprite.xOffset * sprite.xScale,
          texture.height * -sprite.yOffset * sprite.yScale,
          texture.width * sprite.xScale,
          texture.height * sprite.yScale
        )

        // revert translation, hopefully faster than save / restore
        c.rotate(-part.angle)
        c.translate(-part.position.x, -part.position.y)
      } else {
        // part polygon
        if (part.circleRadius) {
          c.beginPath()
          c.arc(
            part.position.x,
            part.position.y,
            part.circleRadius,
            0,
            2 * Math.PI
          )
        } else {
          c.beginPath()
          c.moveTo(part.vertices[0].x, part.vertices[0].y)

          for (let j = 1; j < part.vertices.length; j++) {
            if (!part.vertices[j - 1].isInternal || showInternalEdges) {
              c.lineTo(part.vertices[j].x, part.vertices[j].y)
            } else {
              c.moveTo(part.vertices[j].x, part.vertices[j].y)
            }

            if (part.vertices[j].isInternal && !showInternalEdges) {
              c.moveTo(
                part.vertices[(j + 1) % part.vertices.length].x,
                part.vertices[(j + 1) % part.vertices.length].y
              )
            }
          }

          c.lineTo(part.vertices[0].x, part.vertices[0].y)
          c.closePath()
        }

        if (!options.wireframes) {
          c.fillStyle = part.render.fillStyle
          c.shadowColor = part.render.shadowColor
          c.shadowBlur = part.render.shadowBlur

          if (part.render.lineWidth) {
            c.lineWidth = part.render.lineWidth
            c.strokeStyle = part.render.strokeStyle
            c.stroke()
          }

          c.fill()
        } else {
          c.lineWidth = 1
          c.strokeStyle = "#bbb"
          c.stroke()
        }
      }

      c.globalAlpha = 1
    }
  }
}
function resizeCanvas() {
  canvas.width = window.innerWidth
  canvas.height = window.innerHeight
  Events.off(runner, "beforeUpdate")
  Composite.clear(composite)
  initBodies()
}
function initBodies() {
  // add bodies
  composite = Composite.create()
  for (let i = 0; i < canvas.width / 40; i++) {
    const factor = Common.random(0.2, 1)
    const body = Bodies.circle(
      i * 40,
      canvas.height * Common.random(0, 1),
      8 - 8 * factor,
      {
        render: {
          fillStyle: "#ffff" + Math.round(Common.random(128, 255)).toString(16),
          shadowColor: "#ffffff",
          shadowBlur: 10,
        },
        frictionAir: 0,
        plugin: {
          wrap: {
            min: {
              x: 0,
              y: 0,
            },
            max: {
              x: canvas.width,
              y: canvas.height,
            },
          },
        },
        vY: -factor,
        vMax: factor * Common.random(-1, 1),
        vTime: Common.random(500, 1000),
        vOffset: Common.random(-3, 3),
      }
    )
    Composite.add(composite, body)
  }
  Composite.add(world, composite)
  const bodies = Composite.allBodies(composite)
  Events.on(runner, "beforeUpdate", () => {
    for (let i = 0; i < bodies.length; i++) {
      const body = bodies[i]
      Body.setVelocity(body, {
        x:
          Math.sin(engine.timing.timestamp / body.vTime - body.vOffset) *
          body.vMax,
        y: body.vY,
      })
    }
  })
}
onMounted(() => {
  canvas = document.getElementById("bg") as HTMLCanvasElement
  // create engine
  engine = Engine.create({ gravity: { y: 0 } })
  world = engine.world
  // create renderer
  Render.bodies = newRenderBodies
  render = Render.create({
    canvas: canvas,
    engine: engine,
    options: {
      background: "transparent",
      wireframeBackground: "transparent",
      wireframes: false,
      width: window.innerWidth,
      height: window.innerHeight,
    },
    bodies: newRenderBodies,
  })
  Render.run(render)
  // create runner
  runner = Runner.create()
  Runner.run(runner, engine)
  initBodies()
  window.addEventListener("resize", resizeCanvas)
})
</script>

<template>
  <canvas id="bg"> </canvas>
</template>

<style scoped>
#bg {
  position: fixed;
  top: 0;
  left: 0;
  filter: blur(50);
}
</style>
