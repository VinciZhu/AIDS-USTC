<script setup lang="ts">
import { ref, getCurrentInstance, onMounted } from "vue"
import "aplayer/dist/APlayer.min.css"
import APlayer from "aplayer"
defineProps<{
  name: string
  artist: string
  url: string
  cover: string
  lrc: string
}>()
const instance = getCurrentInstance()
onMounted(() => {
  new APlayer({
    container: document.getElementById("player"),
    theme: "#46718b",
    volume: 0.3,
    lrcType: 3,
    audio: [
      {
        name: instance.props["name"],
        artist: instance.props["artist"],
        url: instance.props["url"],
        cover: instance.props["cover"],
        lrc: instance.props["lrc"],
      },
    ],
  })
})
</script>

<template>
  <div id="player"></div>
</template>

<style scoped>
#player {
  z-index: 99;
  position: absolute;
  width: 100%;
  bottom: 0;
  left: 0;
  right: 0;
  max-width: 800px;
  box-shadow: 0 0 20px rgb(255, 255, 255);
  margin: auto;
}
</style>
