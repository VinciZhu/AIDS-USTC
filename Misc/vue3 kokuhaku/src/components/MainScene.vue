<script setup lang="ts">
import { ref, getCurrentInstance, onMounted } from "vue"
import { gsap } from "gsap"
import AudioPlayer from "./AudioPlayer.vue"
import LightBg from "./LightBg.vue"
import AnimatedText from "./AnimatedText.vue"
import SelectBox from "./SelectBox.vue"
const result = ref(-1)
const tl = gsap.timeline()
const texts = [
  "Dear ???,",
  "Test text 1",
  "Test text 2",
  "Test text 3",
  "Test text 4"
]
const textbox = ref(null)
function changeText() {
  switch (textbox.value.currentIndex) {
    case 1:
      textbox.value.tl.pause()
      tl.resume()
      break
    case 5:
      textbox.value.tl.pause()
      gsap.to("#box", {
        top: 0,
        translateY: 0,
        duration: 1,
        ease: "power4.in",
        onComplete: () => {
          setTimeout(() => {
            result.value = 0
          }, 1000)
        },
      })
      break
  }
}
function procYes() {
  result.value = 1
  gsap.to("#box", {
    opacity: 0,
    duration: 1,
    ease: "power4.in",
    onComplete: () => {
      setTimeout(() => {
        result.value = 1
      }, 1000)
      setTimeout(() => {
        gsap.to("#qrcode", {
          opacity: 1,
          duration: 2,
          ease: "power4.in",
        })
      }, 2000)
    },
  })
}
function procNo() {
  gsap.to("#box", {
    opacity: 0,
    duration: 1,
    ease: "power4.in",
    onComplete: () => {
      setTimeout(() => {
        result.value = 2
      }, 1000)
      setTimeout(() => {
        gsap.to("#failure", {
          opacity: 1,
          duration: 2,
          ease: "power4.in",
        })
      }, 2000)
    },
  })
}
onMounted(() => {
  tl.fromTo(
    "#main-scene",
    { yPercent: -100 },
    {
      yPercent: 0,
      duration: 3,
      ease: "power4.in",
      onComplete: () => {
        textbox.value.tl.resume()
        tl.pause()
      },
    }
  )
  tl.fromTo(
    "#bg",
    { opacity: 0 },
    {
      opacity: 1,
      duration: 2,
      ease: "power4.in",
    }
  )
  tl.fromTo(
    "#player",
    { opacity: 0 },
    {
      opacity: 1,
      duration: 1,
      ease: "power4.in",
      onComplete: () => {
        setTimeout(() => {
          textbox.value.tl.resume()
        }, 1000)
      },
    }
  )
})
</script>

<template>
  <div id="main-scene">
    <LightBg />
    <AudioPlayer name="猫" artist="北村匠海" url="/assets/audio/neko.mp3" cover="/assets/img/dog.jpg"
      lrc="/assets/lyrics/neko.lrc" />
    <AnimatedText ref="textbox" :texts="texts" @nextText="changeText" />
    <div v-if="result === 0">
      <SelectBox head-msg="请选择：" yes-msg="Yes" no-msg="No" @yes="procYes" @no="procNo" />
    </div>
    <div id="qrcode" v-else-if="result === 1">
      <img src="/assets/img/dog.jpg" width="256" height="256" />
    </div>
    <div id="failure" v-else-if="result === 2">我会尊重你的选择。</div>
  </div>
</template>

<style scoped>
#main-scene {
  background-color: rgb(23, 29, 41);
  position: fixed;
  top: 0;
  left: 0;
  height: 100%;
  width: 100%;
  text-align: center;
}

#qrcode,
#failure {
  opacity: 0;
  position: fixed;
  top: 50%;
  width: 100%;
  transform: translateY(-50%);
  background-color: transparent;
  color: rgb(255, 255, 255);
  font-size: 1.5em;
  text-shadow: #ffffff 0px 0px 8px;
}
</style>
