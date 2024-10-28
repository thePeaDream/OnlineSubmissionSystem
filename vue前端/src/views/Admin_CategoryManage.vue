<template>
  <el-container>
    <el-header>稿件类型管理页面</el-header>
    <el-main>
      <el-row>
        <el-col :span="20">
          <el-input v-model="searchKeyword" placeholder="搜索分类名"></el-input>
        </el-col>
        <el-col :span="4">
          <el-button type="primary" @click="openDialog">添加</el-button>
        </el-col>
      </el-row>
      <el-table :data="filteredCategoryList" style="width: 100%">
        <el-table-column prop="categoryId" label="分类 ID" />
        <el-table-column prop="name" label="分类名" />
        <el-table-column fixed="right" label="操作">
          <template slot-scope="scope">
            <el-button type="text" @click="deleteCategory(scope.row)">删除</el-button>
          </template>
        </el-table-column>
      </el-table>
    </el-main>

    <el-dialog title="添加分类" :visible.sync="addDialogVisible">
      <el-input v-model="newCategoryName" placeholder="输入新的分类名称"></el-input>
      <div slot="footer" class="dialog-footer">
        <el-button @click="addDialogVisible = false">取消</el-button>
        <el-button type="primary" @click="addCategory">确定</el-button>
      </div>
    </el-dialog>
  </el-container>
</template>

<script>
import http from '../axios/http.js'
export default {
  data() {
    return {
      searchKeyword: "",
      categoryList: [],
      newCategoryName: "你好",
      addDialogVisible: false
    };
  },
  computed: {
    filteredCategoryList() {
      const keyword = this.searchKeyword.toLowerCase();
      return this.categoryList.filter((category) =>
        category.name.toLowerCase().includes(keyword)
      );
    },
  },
  methods: {
    openDialog() {
      this.addDialogVisible = true;
    },
    addCategory()
    {
      const categoryData = {
        name: this.newCategoryName
      };
      http.post(`/addCategory`,categoryData).then
      (response=>{
          this.categoryList = response.data.categoryList;
          this.addDialogVisible = false;
      }
      )
      .catch(error => {
         console.error('添加稿件类别发生错误', error);
       });
    },
    deleteCategory(category)
    {
      http.post("/removeCategory",category).then
      (response=>{
          this.categoryList = response.data.categoryList;
      }
      )
      .catch(error => {
         console.error('删除稿件类别发生错误', error);
       });
    }
  },
  mounted() {},
  created() {
    http.get("/getAllCategory").then
      (response=>{
          this.categoryList = response.data.categoryList;
      }
      )
      .catch(error => {
         console.error('获取稿件类别发生错误', error);
       });
  }
};
</script>