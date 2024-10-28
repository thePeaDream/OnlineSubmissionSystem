<template>
  <div class="login">
    <div class="mylogin" align="center">
      <h4>在线投稿系统登录</h4>
      <el-form
        :model="loginForm"
        :rules="loginRules"
        ref="loginForm"
        label-width="0px"
      >
        <el-form-item label="" prop="userName" style="margin-top: 10px">
          <el-row>
            <el-col :span="2">
              <span class="el-icon-s-custom"></span>
            </el-col>
            <el-col :span="22">
              <el-input class="inps" placeholder="账号" v-model="loginForm.userName"> </el-input>
            </el-col>
          </el-row>
        </el-form-item>
        <el-form-item label="" prop="password">
          <el-row>
            <el-col :span="2">
              <span class="el-icon-lock"></span>
            </el-col>
            <el-col :span="22">
              <el-input
                class="inps"
                type="password"
                placeholder="密码"
                v-model="loginForm.password"
              ></el-input>
            </el-col>
          </el-row>
        </el-form-item>
        <el-form-item label="">
          <el-radio-group v-model="loginForm.role">
            <el-radio :label="1">作者</el-radio>
            <el-radio :label="2">审核员</el-radio>
            <el-radio :label="3">管理员</el-radio>
          </el-radio-group>
        </el-form-item>
        <el-form-item style="margin-top: 10px">
          <el-button type="primary" round class="submitBtn" @click="submitForm">登录</el-button> <br>
          <router-link :to="{ path: '/register' }"> 作者注册 </router-link> <br>
          <router-link :to="{ path: '/applicationAssessor'}"> 申请成为审核员 </router-link> 
        </el-form-item>
      </el-form>
    </div>
  </div>
</template>

<script>
import http from '../axios/http.js'

export default {
  name: "Login",
  data: function () {
    return {
      loginForm: {
        userName: "",
        password: "",
        role:1
      },
      loginRules: {
        userName: [{ required: true, message: "请输入账号", trigger: "blur" }],
        password: [{ required: true, message: "请输入密码", trigger: "blur" }],
      },
    };
  },
 
  methods: {
    async submitForm() {
      const userAccount = this.loginForm.userName;
      const userPassword = this.loginForm.password;
      if (!userAccount) {
        return this.$message({
          type: "error",
          message: "用户名不能为空！",
        });
      }
      if (!userPassword) {
        return this.$message({
          type: "error",
          message: "密码不能为空！",
        });
      }
      this.loginForm.role = parseInt(this.loginForm.role);
      await http.post("/login",this.loginForm)
       .then(response=>
        {
          console.log("接收到服务器的应答："+response)
          if(response.data.status === "true")
          {
            let sessionId = response.data.sessionId
            let userName = response.data.userName
            let password = response.data.password
            let nickName = response.data.nickName
            let role =response.data.role
            let userId = response.data.userId
            //设置进全局，退出登录时需要手动释放
            localStorage.setItem('sessionId',sessionId)
            localStorage.setItem('userId',userId)
            localStorage.setItem('userName',userName)
            localStorage.setItem('nickName',nickName)
            localStorage.setItem('password',password)
            localStorage.setItem('role',role)
            this.$router.push("/personalCenter")
          }
          else{
            alert("用户名或密码错误，请重试")
          }
        }
        )
        .catch(error=>{
          alert("网络异常，请重试")
        }
      )
     
    }
  },
};
</script>
<style scoped>
  .login {
    width: 100vw;
    padding: 0;
    margin: 0;
    height: 100vh;
    font-size: 16px;
    background-position: left top;
    background-color: #242645;
    color: #fff;
    position: relative;
  }
 
  .mylogin {
    width: 300px;
    height: 300px;
    position: absolute;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    margin: auto;
    padding: 50px 40px 40px 40px;
    box-shadow: -15px 15px 15px rgba(6, 17, 47, 0.7);
    opacity: 1;
    background: black;
  }
 
  .inps input {
    border: none;
    color: #fff;
    background-color: transparent;
    font-size: 12px;
  }
 
  .submitBtn {
    background-color: transparent;
    color: #39f;
    width: 200px;
  }
</style>