<script setup lang="ts">
import { ref, watch, onMounted, getCurrentInstance } from "vue"
import { gsap } from "gsap"
defineProps<{ TargerId: string; headMsg: string; placeholderMsg: string }>()
defineEmits<{ (e: "verify"): void }>()
const input = ref("")
const verified = ref(false)
const instance = getCurrentInstance()
onMounted(() => {
  gsap.fromTo(
    "#id-box",
    { scaleY: 0, opacity: 0 },
    { scaleY: 1, opacity: 1, duration: 0.5 }
  )
})
watch(
  () => input.value,
  (input) => {
    if (input === instance.props["TargerId"]) {
      verified.value = true
      gsap.to("#id-box", {
        delay: 0.5,
        scaleY: 0,
        opacity: 0,
        duration: 0.25,
        onComplete: () => {
          instance.emit("verify")
        },
      })
    }
  }
)
</script>

<template>
  <el-container id="id-box">
    <el-header>{{ headMsg }}</el-header>
    <el-main>
      <el-input
        autofocus="true"
        v-model="input"
        :placeholder="placeholderMsg"
        :disabled="verified"
    /></el-main>
  </el-container>
</template>

<style scoped>
.el-header {
  background-color: #728bac;
  color: white;
  font-weight: bold;
  text-shadow: #424242 0px 0px 8px;
  text-align: center;
  line-height: 60px;
}

.el-main {
  background-color: #e9eef3;
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
