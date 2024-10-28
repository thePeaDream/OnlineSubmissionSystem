// 导入axios
import axios from 'axios'

//1. 创建新的axios实例，
const instance = axios.create({
  // 服务器基础URL
  baseURL: 'http://114.132.234.12:8080',
  // 超时时间 单位是ms，这里设置了12s的超时时间
  timeout: 20 * 1000,
  withCredentials: true
});

// 2.请求拦截器
instance.interceptors.request.use(config => {
  const sessionId = localStorage.getItem('sessionId')
  console.log("请求服务器之前先将sessionId设进请求头")
  if(sessionId){
  }
  config.headers['Content-Type'] = 'application/json;charset=UTF-8';
  return config
}, error => {
  console.log('错误')
  return Promise.reject(error)
})


//3 导出
export default instance;