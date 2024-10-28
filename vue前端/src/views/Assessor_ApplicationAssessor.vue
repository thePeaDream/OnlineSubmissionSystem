<template>
  <div class="box">
    <div class="application" align="center">
      <h3>在线投稿系统审核员申请</h3>
      <el-form
        :model="ruleForm"
        :rules="rules"
        ref="ruleForm"
        label-width="80px"
      >
        <el-form-item label="用户名" prop="userName" style="margin-top: 20px">
          <el-input v-model="ruleForm.userName" class="inps" ></el-input>
        </el-form-item>
        <el-form-item label="昵称" prop="nickName">
          <el-input v-model="ruleForm.nickName" class="inps" ></el-input>
        </el-form-item>
        <el-form-item label="密码" prop="password">
          <el-input type="password" v-model="ruleForm.password" class="inps"></el-input>
        </el-form-item>
        <el-form-item label="确认密码" prop="confirmPassword">
          <el-input type="password" v-model="ruleForm.confirmPassword" class="inps"></el-input>
        </el-form-item>
        <el-form-item label="手机号码" prop="phone">
          <el-input v-model="ruleForm.phone" class="inps"></el-input>
        </el-form-item>
        <el-form-item label="个人描述" prop="description">
          <el-input type="textarea" placeholder="请输入内容" v-model="ruleForm.description" maxlength="300" rows = "10" resize="none"></el-input>
        </el-form-item>
        <el-form-item label="擅长类别" prop="category">
            <el-select v-model="ruleForm.categoryId" filterable placeholder="请选择">
                <el-option v-for="item in category" :key="item.categoryId" :label="item.name" :value="item.categoryId"></el-option>
            </el-select>
        </el-form-item>
        <el-form-item>
            <el-button type="primary" @click="submitForm()" class="submitBtn" round> 注册 </el-button> <br>
            <router-link :to="{ path: '/login' }"> 返回登录 </router-link>
        </el-form-item>
      </el-form>
    </div>
  </div>
</template>
<script>
import http from '../axios/http.js';
export default {
  data() {
     const checkUserName = (rule, value, callback)=>{
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
    const checkNickName = (rule, value, callback)=>{
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
    const checkDescription = (rule, value, callback)=>{
        if(value === ""){
            callback(new Error("个人描述不能为空！！！！"))
        }else{
            callback()
        }
    };
    return {
      category:[],
      ruleForm: {
        userName: "",
        nickName:"",
        password: "",
        confirmPassword: "",
        phone: "",
        description:"",//个人描述
        categoryId:""
      },
      rules: {
        userName: [{ validator: checkUserName, trigger: "blur" }],
        nickName:[{ validator: checkNickName, trigger: "blur"}],
        password: [{ validator: checkPassword1, trigger: "blur" }],
        confirmPassword: [{ validator: checkPassword2, trigger: "blur" }],
        phone: [{ validator: checkPhone, trigger: "blur" }],
        description:[{ validator: checkDescription, trigger: "blur" }],
      },
    }
  },
  created() {
    http.get(`/getAllCategory`)
     .then(response => {
        console.log(response)
        this.category = response.data.categoryList;
      })
     .catch(error => {
        console.error('获取稿件类别请求失败:', error);
      });
  },
  methods: {
    returnForm() {
      // 返回login界面
      this.$router.push("/login");
    },
    submitForm() {
      //如果表单数据全部合法，就提交
      if(this.isFormValid){
          //提交表单数据给对应服务，注册成功返回进入登录页面
          http.post(`/applicationAssessor`,this.ruleForm)
          .then(response=>
          {
              if(response.data.status === "true"){
              alert("成功完成申请，请等待管理员审核通过方可进入系统")
              this.$router.push("/login")
            }
            else{
              alert("用户名、昵称或电话号码已被占用！！！请重试")
            }
          }
          )
          .catch(error=>{
            console.log(error)
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
             this.isValidPhone &&
             this.isValidDescription&&
             this.isValidCategoryName;
    },
    isValidUserName() {
      const regUser = /^[a-zA-Z0-9]{3,12}$/;
      return regUser.test(this.ruleForm.userName);
    },
    isValidNickName(){
        return this.ruleForm.nickName !== ""; 
    },
    isValidPassword() {
      const regPass = /^\d{8,15}$/;
      return regPass.test(this.ruleForm.password);
    },
    isPasswordsMatch() {
      return this.ruleForm.password === this.ruleForm.confirmPassword;
    },
    isValidPhone() {
      const regPhone = /^\d{11}$/;
      return regPhone.test(this.ruleForm.phone);
    },
    isValidDescription(){
        return this.ruleForm.description !== "";
    },
    isValidCategoryName(){
        return this.ruleForm.categoryName !== ""; 
    }
  },
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
.application {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  width: 700px;
  height: 780px;
  background-color: #fff;
  border-radius: 3px;
}
.el-form-item {
  margin-top: 20px;
  width: 600px;
}
.submitBtn {
    background-color: transparent;
    color: #39f;
    width: 300px;
    margin-left:5px;
    margin-top:10px;
}
</style>
