import Vue from "vue"
import VueRouter from "vue-router"
//通用组件
import Login from '../components/Login.vue'   //登录
import Struct from '../components/Struct.vue' //页面结构
import PersonalCenter from '../components/PersonalCenter.vue' //个人信息中心
import HistoryNotice from '../components/HistoryNotice.vue' //历史通知
import Home from '../components/Home.vue'//系统主页 —— 所有已公开稿件列表
//作者组件
import HistoryManuscript from '../views/Writer_HistoryManuscript.vue' //历史投稿
import Submit from '../views/Writer_Submit.vue'  //投稿页面
import Register from '../views/Writer_Register.vue' //注册
//审核组件
import ManuscriptAudit from '../views/Assessor_ManuscriptAudit.vue' //稿件审核 
import ApplicationAssessor from '../views/Assessor_ApplicationAssessor.vue' //申请成为审核员
//管理员组件
import WriterManage from '../views/Admin_WriterManage.vue' //作者管理
import AssessorManage from '../views/Admin_AssessorManage.vue' //审核管理
import ManuscriptManage from '../views/Admin_ManuscriptManage.vue'//稿件管理
import PublishNotice from '../views/Admin_PublishNotice.vue' //发布通知
import LogManage from '../views/Admin_LogManage.vue'//日志管理
import CategoryManage from '../views/Admin_CategoryManage.vue' //稿件类别管理
import AssessorApplicationManage from '../views/Admin_AssessorApplicationManage.vue'//申请审核员管理



//将 VueRouter 插件安装到 Vue.js 实例中，就可以在 Vue 应用中使用路由功能
Vue.use(VueRouter)

//描述应用的路由配置
const routes = 
[
    {
        //登录
        path:'/login',
        component:Login
    },
    {
        //注册
        path:'/register',
        component:Register
    },
    {
        //申请成为审核员
        path:'/applicationAssessor',
        component:ApplicationAssessor
    },
    {
        path:'/',
        component:Struct,
        redirect:'/login',
        children:[
          {path:'/personalCenter',component: PersonalCenter},
          {path:'/historyNotice',component: HistoryNotice},

          //作者组件
          {path: '/historyManuscript', component: HistoryManuscript},
          {path:'/submitManuscript',component: Submit},
          {path:'/home',component:Home},
          
          //审核组件
          {path:'/manuscriptAudit',component:ManuscriptAudit},

          //管理员组件
          {path:'/writerManage',component:WriterManage},
          {path:'/assessorManage',component:AssessorManage},
          {path:'/assessorApplicationManage',component:AssessorApplicationManage},
          {path:'/manuscriptManage',component:ManuscriptManage},
          {path:'/publishNotice',component:PublishNotice},
          {path:'/logManage',component:LogManage},
          {path:'/categoryManage',component:CategoryManage}
        ]
    }
]

const router = new VueRouter({
    routes:routes
})
export default router;