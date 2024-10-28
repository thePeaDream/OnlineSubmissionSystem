<template>
  <el-container>
    <el-header>
      <h2 style="text-align:center; margin-top=10px;">发布通知</h2>
    </el-header>
    <el-main>
      <el-form :model="notice" ref="noticeForm" label-width="80px">
        <el-form-item label="标题" prop="title" :rules="[{ required: true, message: '请输入通知标题', trigger: 'blur' }]">
          <el-input v-model="notice.title" placeholder="请输入通知标题"></el-input>
        </el-form-item>
        <el-form-item label="内容" prop="content" :rules="[{ required: true, message: '请输入通知内容', trigger: 'blur' }]">
          <el-input type="textarea" v-model="notice.content" placeholder="请输入通知内容" rows="12" resize="none"></el-input>
        </el-form-item>
        <el-form-item>
          <el-button type="primary" @click="submitNotice">发布通知</el-button>
        </el-form-item>
      </el-form>
    </el-main>
  </el-container>
</template>

<script>
import http from '../axios/http.js'
export default {
  data() {
    return {
      notice: {
        title: '',
        content: ''
      },
    };
  },
  methods: {
    submitNotice() {
      this.$refs.noticeForm.validate(valid => {
        if (valid) {
          http.post("/addNotice",this.notice).then
          (response=>{
            this.$message.success('通知发布成功');
            this.resetForm();
          }
          )
          .catch(error => {
            console.error('发布失败', error);
          });
          
        } else {
          this.$message.error('请检查输入');
          return false;
        }
      });
    },
    resetForm() {
      this.notice.title = '';
      this.notice.content = '';
      this.$refs.noticeForm.resetFields();
    }
  },
  created() {
       
  },
};
</script>

<style scoped>
.el-form {
  max-width: 600px;
  margin: 20px auto;
}
</style>