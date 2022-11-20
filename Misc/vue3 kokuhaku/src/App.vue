<script setup lang="ts">
  import { ref } from "vue"
  import IdentifyBox from "./components/IdentifyBox.vue"
  import PopMessage from "./components/PopMessage.vue"
  import MainScene from "./components/MainScene.vue"
  const stage = ref(0)
  function nextStage() {
    stage.value++
  }
  </script>
  
  <template>
    <span v-if="stage === 0">
      <IdentifyBox TargerId="zyq" headMsg="身份验证" placeholderMsg="你是谁?(首字母缩写)" @verify="nextStage" />
    </span>
    <span v-else-if="stage === 1">
      <PopMessage msg="验证通过" @timeout="nextStage" />
    </span>
    <span v-else-if="stage === 2">
      <MainScene />
    </span>
  </template>
  
  <style>
  #app {
    position: fixed;
    top: 0;
    left: 0;
    height: 100%;
    width: 100%;
    font-family: Avenir, Helvetica, Arial, "Microsoft YaHei", "宋体", sans-seri;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-align: center;
    color: rgb(0, 0, 0);
  }
  </style>
  