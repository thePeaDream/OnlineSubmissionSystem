<template>
  <div class="box">
    <div class="zhuce" align="center">
      <h3>在线投稿系统注册</h3>
      <el-form
        :model="ruleForm"
        :rules="rules"
        ref="ruleForm"
        label-width="80px"
      >
        <el-form-item label="用户名" prop="userName" style="margin-top: 20px">
          <el-input v-model="ruleForm.userName" class="inps" ></el-input>
        </el-form-item>
        <el-form-item label="昵称" prop="nickName" style="margin-top: 20px">
          <el-input v-model="ruleForm.nickName" class="inps" ></el-input>
        </el-form-item>
        <el-form-item label="密码" prop="password">
          <el-input type="password" v-model="ruleForm.password" class="inps"></el-input>
        </el-form-item>
        <el-form-item label="确认密码" prop="confirmPassword">
          <el-input type="password" v-model="ruleForm.confirmPassword" class="inps"></el-input>
        </el-form-item>
        <el-form-item label="手机号码" prop="phone">
          <el-input v-model="ruleForm.phone" class="inps" ></el-input>
        </el-form-item>
        <el-button type="primary" @click="submitForm()" class="submitBtn" round> 注册 </el-button>
        <div class="returnLogin">
            <router-link :to="{ path: '/login' }"> 返回登录 </router-link>
        </div>
      </el-form>
    </div>
  </div>
</template>
<script>
export default {
  data() {
     const checkUsername = (rule, value, callback)=>{
      const regUser = /^[a-zA-Z0-9]{3,12}$/
      if (value === "") 
      {
        callback(new Error("用户名不能为空"))
      } 
      else if(!regUser.test(value))
      {
        callback(new Error("用户名必须为3~12位字母或数字"));
      }
      else{
        callback()
      }
    };
    const checkNickname = (rule, value, callback)=>{
      if (value === "") 
      {
        callback(new Error("昵称不能为空"))
      } 
      else{
        callback()
      }
    };
    const checkPassword1=(rule, value, callback)=> {
      const regUser = /^\d{8,15}$/;
      if (value === "") {
        callback(new Error("请输入密码"));
      } else if(!regUser.test(value))
      {
        callback(new Error("密码长度必须为8~15"));
      }
      else{
        callback()
      }
    };
    const checkPassword2= (rule, value, callback)=>{
      if (value === "") {
        callback(new Error("请再次输入密码"));
      } else if (value !== this.ruleForm.password) {
        callback(new Error("两次输入密码不一致!"));
      } else {
        callback();
      }
    };
    const checkPhone= (rule, value, callback)=>{
      const regUser = /^\d{11}$/;
      if (value && regUser.test(value)) {
        callback();
      } else {
        callback(new Error("手机号码必须是11位数字"));
      }
    };
    return {
      ruleForm: {
        userName: "",
        nickName:"",
        password: "",
        confirmPassword: "",
        phone: "",
      },
      rules: {
        userName: [{ validator: checkUsername, trigger: "blur" }],
        nickName:[{validator:checkNickname, trigger:"blur"}],
        password: [{ validator: checkPassword1, trigger: "blur" }],
        confirmPassword: [{ validator: checkPassword2, trigger: "blur" }],
        phone: [{ validator: checkPhone, trigger: "blur" }]
      },
    }
  },
  methods: {
    returnForm() {
      // 返回login界面
      this.$router.push("/login");
    },
    submitForm() {
      //如果表单数据全部合法，就提交
      if(this.isFormValid){
          console.log(this.$http)
          //提交表单数据给对应服务，注册成功返回进入登录页面
          this.$axios.post("http://114.132.234.12:8080/register",this.ruleForm)
          .then((response)=>{
            console.log(response)
             if(response.data.status === "true"){
              alert("注册成功！！！")
              this.$router.push("/login")
            }
            else{
              console.log(response)
              alert("用户名、昵称或电话号码已被占用！！！请重试")
            }
          }
          )
          .catch(error=>{
            console.log(error)
            alert("注册发生错误，请重试")
          }
          )
      }

    }
  },
  computed: {
    //当前表单的输入是否全部合法
    isFormValid() {
      return this.isValidUserName &&
             this.isValidNickName &&
             this.isValidPassword &&
             this.isPasswordsMatch &&
             this.isValidPhone
    },
    isValidUserName() {
      const regUser = /^[a-zA-Z0-9]{3,12}$/;
      return regUser.test(this.ruleForm.userName);
    },
    isValidPassword() {
      const regPass = /^\d{8,15}$/;
      return regPass.test(this.ruleForm.password);
    },
    isValidNickName() {
      return this.ruleForm.nickName!=="";
    },
    isPasswordsMatch() {
      return this.ruleForm.password === this.ruleForm.confirmPassword;
    },
    isValidPhone() {
      const regPhone = /^\d{11}$/;
      return regPhone.test(this.ruleForm.phone);
    }
  }
};
</script>
<style scoped>
.box {
  height: 100%;
  background-color: #2e4e6e;
}
h3{
  margin-top:10px;
}
.zhuce {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  width: 450px;
  height: 450px;
  background-color: #fff;
  border-radius: 3px;
}
.el-form-item {
  margin-top: 20px;
  width: 400px;
}
.submitBtn {
    background-color: transparent;
    color: #39f;
    width: 300px;
    margin-left:40px;
}
.returnLogin{
  margin-top:10px;
  margin-left:30px;
}
</style>
