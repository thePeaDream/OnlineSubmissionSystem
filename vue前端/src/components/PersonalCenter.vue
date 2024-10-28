<template>
  <div>
    <el-descriptions class="margin-top" title="基本信息" :column="1" border style="margin-top:20px;">
      <template slot="extra">
        <el-button type="primary" size="small" @click="openEditDialog">编辑</el-button>
      </template>
      <el-descriptions-item>
        <template slot="label">
          <i class="el-icon-mobile-phone"></i>
          userId
        </template>
        {{userId}}
      </el-descriptions-item>
      <el-descriptions-item>
        <template slot="label">
          <i class="el-icon-location-outline"></i>
          role
        </template>
        {{role | roleFilter}}
      </el-descriptions-item>
      <el-descriptions-item>
        <template slot="label">
          <i class="el-icon-tickets"></i>
          nickName
        </template>
        {{nickName}}
      </el-descriptions-item>
      <el-descriptions-item>
        <template slot="label">
          <i class="el-icon-office-building"></i>
          userName
        </template>
        {{userName}}
      </el-descriptions-item>
      <el-descriptions-item>
        <template slot="label">
          <i class="el-icon-office-building"></i>
          phone
        </template>
        {{phone}}
      </el-descriptions-item>
    </el-descriptions>
    <!-- 编辑对话框 -->
    <el-dialog title="编辑基本信息" :visible.sync="editDialogVisible">
      <el-form :data="editForm">
        <el-form-item label="用户id">
          <el-input v-model="editForm.userId" disabled></el-input>
        </el-form-item>
        <el-form-item label="昵称">
          <el-input v-model="editForm.nickName"></el-input>
        </el-form-item>
        <el-form-item label="用户名">
          <el-input v-model="editForm.userName" disabled></el-input>
        </el-form-item>
        <el-form-item label="密码">
          <el-input v-model="editForm.password" type="password"></el-input>
        </el-form-item>
        <el-form-item label="电话">
          <el-input v-model="editForm.phone"></el-input>
        </el-form-item>
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button @click="editDialogVisible = false">取消</el-button>
        <el-button type="primary" @click="saveEditedInfo">确定</el-button>
      </div>
    </el-dialog>
  </div>
</template>

<script>
import http from '../axios/http.js'
const roleNumberToNameMap = { 1:'Writer', 2:'Assessor', 3:'Admin'};
const roleNameToNumberMap = {'Writer':1, 'Assessor':2, 'Admin':3};
export default {
  data() {
    return {
      userId: 1,
      role: 1,
      nickName: '',
      userName: '',
      password: '',
      phone: '',
      editDialogVisible: false,
      editForm: {
        userId:'',
        nickName: '',
        userName: '',
        password: '',
        phone: ''
      }
    };
  },
  methods: {
    openEditDialog() {
      this.editForm.userId = this.userId;
      this.editForm.nickName = this.nickName;
      this.editForm.userName = this.userName;
      this.editForm.password = this.password;
      this.editForm.phone = this.phone;
      this.editDialogVisible = true;
    },
    saveEditedInfo() {
      http.post("/updatePersonalInformation",this.editForm)
      .then(response=> {
        this.userId = response.data.userId;
        this.nickName = response.data.nickName;
        this.userName = response.data.userName;
        this.password = response.data.password;
        this.phone = response.data.phone;
         this.editDialogVisible = false;
       })
      .catch(error => {
         console.error('保存编辑信息发生错误', error);
       })
    }
    },
  created() {
    const userName = localStorage.getItem('userName');
    const password = localStorage.getItem('password');
    http.get(`/getPersonalInformation?userName=${userName}&password=${password}`).then
      (response=>{
          this.userId = response.data.userId;
          this.role = response.data.role;
          localStorage.setItem("role",this.role);
          this.nickName = response.data.nickName;
          this.userName = response.data.userName;
          this.password =  response.data.password;
          this.phone = response.data.phone;
      }
      )
      .catch(error => {
         console.error('请求个人信息发生错误', error);
       });
  },
  filters: {
      roleFilter(roleValue) {
          return roleNumberToNameMap[roleValue];
      }
  }
};
</script>

<style scoped>
</style>