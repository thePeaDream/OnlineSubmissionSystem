<template>
  <div>
    <el-container>
      <!--侧边栏导航-->
      <el-aside style="width:200px;min-height: 100vh">
        <component :is="asideComponent" />
      </el-aside>

      <el-container>
        <el-header style="background-color: lightgreen;position: fixed;width: 100%;">
          <div class="user-info">
            <div style="margin-top:20px;margin-left:20px;margin-right:10px;">欢迎</div>
            <span @click="logout" style="color: blue;cursor: pointer;margin-top:20px;">退出登录</span>
          </div>
        </el-header>

        <el-main style="padding-top: 60px;">
          <router-view></router-view>
        </el-main>
      </el-container>

    </el-container>
  </div>
</template>

<script>
import WriterAside from "./WriterAside.vue";
import AssessorAside from "./AssessorAside.vue";
import AdminAside from "./AdminAside.vue";
import http from '../axios/http.js'
export default {
  data() {
    return {
      role: 1,
      nickName:""
    };
  },
  methods:{
    logout() {
      // 在这里执行退出登录的特定函数逻辑

      // 1 清除本地存储中的登录信息等操作
      localStorage.removeItem('role');
      localStorage.removeItem('nickName');
      localStorage.removeItem('userName');
      localStorage.removeItem('password');
      
      // 2 进行页面跳转或其他操作
      this.$router.push("/login")
    }
  },
  computed: {
    asideComponent() {
      if (this.role == 3) return AdminAside;
      else if (this.role == 2) return AssessorAside;
      else if (this.role == 1) return WriterAside;
    },
  },
  components: {
    WriterAside,
    AssessorAside,
    AdminAside,
  },
  created(){
    const userName = localStorage.getItem('userName');
    const password = localStorage.getItem('password');
    http.get(`/getPersonalInformation?userName=${userName}&password=${password}`).then
      (response=>{
          this.role = response.data.role;
          this.nickName = response.data.nickName;
          localStorage.setItem("role",this.role);
      }
      )
      .catch(error => {
         console.error('请求个人信息发生错误', error);
       });
  }
};
</script>

<style scoped>
.user-info {
  display: flex;
  justify-content: center;
}
</style>