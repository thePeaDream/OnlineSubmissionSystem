<template>
  <div class="manuscript-upload-container">
    <el-container>
      <el-header>
        <h2 style="text-align: center;">上传稿件</h2>
      </el-header>
      <el-main>
        <el-form :model="manuscript" ref="manuscriptForm" label-width="120px">
          <el-form-item label="稿件名" prop="name" :rules="[{ required: true, message: '请输入稿件名', trigger: 'blur' }]">
            <el-input v-model="manuscript.name" placeholder="请输入稿件标题"></el-input>
          </el-form-item>

          <el-form-item label="类别" prop="categoryList">
            <el-select v-model="manuscript.categoryId" filterable placeholder="请选择">
                <el-option v-for="item in categoryList" :key="item.categoryId" :label="item.name" :value="item.categoryId"></el-option>
            </el-select>
          </el-form-item>

          <el-form-item label="稿件内容" prop="description" :rules="[{ required: true, message: '内容不能为空', trigger: 'blur' }]">
            <el-input type="textarea" v-model="manuscript.description" placeholder="请输入稿件内容" rows="25" resize="none" ></el-input>
          </el-form-item>
          <el-form-item>
            <el-button type="primary" @click="submitManuscript">发布稿件</el-button>
          </el-form-item>
        </el-form>
      </el-main>
    </el-container>
  </div>
</template>

<script>
import http from '../axios/http.js'
export default {
  data() {
    return {
      categoryList:[],
      manuscript: {
        name: '',
        description: '',
        categoryId:'',
        writerId:0
      }
    };
  },
  methods: {
    resetForm()
    {
      this.manuscript.name = "";
      this.manuscript.description = "";
      this.categoryId = "";
    },
    submitManuscript() {
      console.log(this.manuscript)
      http.post("/submitPersonalManuscript",this.manuscript).then
          (response=>{
            console.log(response)
            this.$message.success('稿件发布成功');
            this.resetForm();
          }
          )
          .catch(error => {
            console.error('发布失败', error);
          });
    }
  },
  mounted(){
    this.manuscript.writerId = localStorage.getItem("userId");
    http.get('/getAllCategory')
      .then(response => {
          console.log(response)
              this.categoryList = response.data.categoryList;
              this.manuscript.writerId =parseInt(localStorage.getItem("userId"));
              })
              .catch(error => {
                  console.error('Error fetching categories:', error);
              });
    
  }
};
</script>

<style scoped>
.manuscript-upload-container {
  padding: 20px;
}
.el-header {
  background-color: #f8f8f8;
}
h2 {
  color: #333;
  font-weight: bold;
}
.el-form-item label {
  font-size: 16px;
  color: #555;
}
.el-input__textarea {
  border: 1px solid #ccc;
  border-radius: 4px;
}
.el-button {
  margin-top: 20px;
}
</style>