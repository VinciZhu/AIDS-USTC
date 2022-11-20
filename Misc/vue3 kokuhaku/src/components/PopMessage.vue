<script setup lang="ts">
import { ref, getCurrentInstance, onMounted } from "vue"
import { gsap } from "gsap"
defineProps<{ msg: string }>()
defineEmits<{ (e: "timeout"): void }>()
const instance = getCurrentInstance()
onMounted(() => {
  gsap.fromTo(
    "#msg-box",
    { scaleX: 0, opacity: 0 },
    { delay: 0.5, scaleX: 1, opacity: 1, duration: 1, ease: "power4.out" }
  )
  gsap.to("#msg-box", {
    delay: 2,
    opacity: 0,
    duration: 0.5,
    ease: "power4.in",
    onComplete: () => {
      instance.emit("timeout")
    },
  })
})
</script>

<template>
  <div id="msg-box">
    {{ msg }}
  </div>
</template>

<style scoped>
#msg-box {
  position: relative;
  top: 50%;
  width: 100%;
  background-color: #ccced1;
  color: rgb(0, 128, 17);
  font-size: 2em;
  text-shadow: #ffffff 0px 0px 8px;
  transform: translateY(-50%);
  text-align: center;
}
</style>
