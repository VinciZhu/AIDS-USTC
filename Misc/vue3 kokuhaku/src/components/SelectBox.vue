<script setup lang="ts">
import { ref, onMounted, getCurrentInstance } from "vue"
import { gsap } from "gsap"
defineProps<{ headMsg: string; yesMsg: string; noMsg: string }>()
defineEmits<{ (e: "yes"): void; (e: "no"): void }>()
const selected = ref(false)
const instance = getCurrentInstance()
onMounted(() => {
  gsap.fromTo(
    "#sl-box",
    { scaleY: 0, opacity: 0 },
    { scaleY: 1, opacity: 1, duration: 0.5 }
  )
})
function procYes() {
  selected.value = true
  gsap.to("#sl-box", {
    delay: 0.5,
    scaleY: 0,
    opacity: 0,
    duration: 0.25,
    onComplete: () => {
      instance.emit("yes")
    },
  })
}
function procNo() {
  selected.value = true
  gsap.to("#sl-box", {
    delay: 0.5,
    scaleY: 0,
    opacity: 0,
    duration: 0.25,
    onComplete: () => {
      instance.emit("no")
    },
  })
}
</script>

<template>
  <el-container id="sl-box">
    <el-header>{{ headMsg }}</el-header>
    <el-main>
      <el-button @click="procYes" type="success" round :disabled="selected">{{
        yesMsg
      }}</el-button>
      <el-button @click="procNo" type="danger" round :disabled="selected">{{
        noMsg
      }}</el-button>
    </el-main>
  </el-container>
</template>

<style scoped>
.el-header {
  background-color: #313f46;
  color: white;
  font-weight: bold;
  text-shadow: #424242 0px 0px 8px;
  text-align: center;
  line-height: 60px;
}

.el-main {
  background-color: #ffffff7e;
  color: var(--el-text-color-primary);
  text-align: center;
  line-height: 40px;
}

.el-container {
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  width: 320px;
  height: 150px;
  margin: auto;
}
</style>
