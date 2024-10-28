import Vue from 'vue'
import App from './App.vue'
//路由引入
import router from './router/index.js'

//element-ui引入
import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'
import { mapMutations } from 'vuex'

import axios from 'axios'


Vue.prototype.$axios = axios



Vue.use(ElementUI)

new Vue({
  router,
  mapMutations,
  render:(createElement) =>{
    return createElement(App)
  }
}).$mount('#app')

