// eslint-disable-next-line @typescript-eslint/ban-ts-comment
// @ts-ignore

import { createApp } from "vue"
import App from "./App.vue"

import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'

import { gsap } from "gsap"
import { TextPlugin } from "gsap/TextPlugin.js"

import Matter from "matter-js"
import MatterWrap from "matter-wrap"

gsap.registerPlugin(TextPlugin)
Matter.use(MatterWrap)
createApp(App).use(ElementPlus).mount('#app')