<script setup lang="ts">
import { ref, getCurrentInstance, onMounted } from "vue"
import { gsap } from "gsap"
defineProps<{ texts: Array<string> }>()
const instance = getCurrentInstance()
const currentIndex = ref(0)
const tl = gsap.timeline()
function nextText() {
  currentIndex.value++
  instance.emit("nextText")
}
onMounted(() => {
  tl.pause()
  tl.to("#box", { opacity: 1, duration: 0.5 })
  const texts = instance.props.texts as Array<string>
  for (let index = 0; index < texts.length; index++) {
    tl.fromTo(
      "#text",
      { text: { value: "" }, opacity: 1 },
      {
        text: { value: texts[index], speed: 0.4 },
        duration: texts[index].length * 0.2,
      }
    )
    tl.to("#text", { onStart: nextText, opacity: 0, duration: 0.5 })
  }
  tl.to("#box", { onStart: nextText, opacity: 0, duration: 0.5 })
})
defineExpose({ currentIndex, tl })
</script>

<template>
  <div id="box">
    <div id="text"></div>
  </div>
</template>

<style scoped>
#box {
  position: relative;
  top: 50%;
  width: 100%;
  height: 50%;
  background-color: #0000006b;
  opacity: 0;
  transform: translateY(-50%);
}
#text {
  position: relative;
  top: 50%;
  width: 100%;
  background-color: transparent;
  color: rgb(255, 255, 255);
  font-size: 1.5em;
  text-shadow: #ffffff 0px 0px 8px;
  transform: translateY(-50%);
}
</style>
