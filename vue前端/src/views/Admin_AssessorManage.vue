<template>
  <div style="margin-top:10px;">
    <el-input placeholder="按昵称查找审核员" v-model="searchNickName" @input="searchAssessors" ></el-input>
    <el-table :data="assessors" style="margin-top: 20px">
      <el-table-column prop="assessorId" label="审核员 ID"></el-table-column>
      <el-table-column prop="nickName" label="昵称"></el-table-column>
      <el-table-column prop="applicationTime" label="申请时间"></el-table-column>
      <el-table-column prop="categoryId" label="擅长类别ID"></el-table-column>
      <el-table-column prop="pendingAudit" label="待审核稿件数目"></el-table-column>
      <el-table-column label="操作">
        <template v-slot="{ row }">
          <el-button type="danger" @click="remove(row)">删除</el-button>
          <el-button type="primary" @click="viewDetail(row)">详情</el-button>
        </template>
      </el-table-column>
    </el-table>
    <el-dialog title="审核员详情" :visible.sync="editDialogVisible" style="margin-top:-150px;">
      <el-form :data="editForm">
        <el-form-item label="审核员id">
          <el-input v-model="editForm.assessorId" disabled></el-input>
        </el-form-item>
        <el-form-item label="昵称">
          <el-input v-model="editForm.nickName" disabled></el-input>
        </el-form-item>
        <el-form-item label="用户名">
          <el-input v-model="editForm.userName" disabled></el-input>
        </el-form-item>
        <el-form-item label="密码">
          <el-input v-model="editForm.password" type="password" disabled></el-input>
        </el-form-item>
        <el-form-item label="电话">
          <el-input v-model="editForm.phone" disabled></el-input>
        </el-form-item>
        <el-form-item label="申请成为审核的时间">
          <el-input v-model="editForm.applicationTime" disabled></el-input>
        </el-form-item>
        <el-form-item label="个人描述">
          <el-input v-model="editForm.description" type="textarea"  maxlength="300" rows = "10" resize="none" disabled></el-input>
        </el-form-item>
        <el-form-item label="擅长稿件类型">
          <el-input v-model="editForm.categoryId" disabled></el-input>
        </el-form-item>
        <el-form-item label="待审核稿件数">
          <el-input v-model="editForm.pendingAudit" disabled></el-input>
        </el-form-item>
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button @click="editDialogVisible = false">取消</el-button>
      </div>
    </el-dialog>
  </div>
</template>

<script>
import http from '../axios/http.js'
export default {
  data() {
    return {
      searchNickName: '',
      assessors: [],
      editDialogVisible: false,
      editForm: {
        assessorId:'',
        nickName: '',
        userName: '',
        password: '',
        phone: '',
        applicationTime:'',
        description:'',
        categoryId:'',
        pendingAudit:''
      }
    };
  },
  methods: {
    searchAssessors() {
      if (this.searchNickName === '') {
        http.get("/getFormalAssessor").then
        (response=>{
            this.assessors = response.data.formalAssessorList;
        }
        )
        .catch(error => {
          console.error('获取审核员列表失败', error);
        });
      } else {
        const filteredAssessors = this.assessors.filter(assessor => assessor.nickName.includes(this.searchNickName));
        this.assessors = filteredAssessors;
      }
    },
    viewDetail(row) {
      this.editForm.assessorId = row.assessorId;
      this.editForm.nickName =  row.nickName;
      this.editForm.userName =  row.userName;
      this.editForm.password =  row.password;
      this.editForm.phone =  row.phone;
      this.editForm.applicationTime =  row.applicationTime;
      this.editForm.description = row.description;
      this.editForm.assessorId =  row.assessorId;
      this.editForm.categoryId = row.categoryId;
      this.editForm.pendingAudit = row.pendingAudit;
      this.editDialogVisible = true;
    },
    remove(row)
    {
        http.post("/removeAssessor",row).then
        (response=>{
            this.assessors = response.data.formalAssessorList;
            
          }
        )
        .catch(error => {
            console.error('删除失败', error);
        });
        
    },
  },
  getCategoryName(categoryId) {
      const category = localStorage.getItem('categoryList').find(item => item.categoryId === categoryId);
      return category? category.categoryName : '未知类别';
    },
  created() {
    http.get("/getFormalAssessor").then
      (response=>{
          this.assessors = response.data.formalAssessorList;
      }
      )
      .catch(error => {
         console.error('获取审核员列表失败', error);
       });
  }
};
</script>

<style>
.el-table {
  width: 100%;
}
</style>