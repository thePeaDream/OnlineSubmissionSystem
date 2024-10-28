<template>
  <div style="margin-top:10px;">
    <el-input placeholder="按昵称查找作者" v-model="searchNickName" @input="searchAuthors"></el-input>
    <el-table :data="authors" style="margin-top: 20px">
      <el-table-column prop="writerId" label="作者ID"></el-table-column>
      <el-table-column prop="nickName" label="昵称"></el-table-column>
      <el-table-column prop="userName" label="用户名"></el-table-column>
      <el-table-column prop="password" label="密码"></el-table-column>
      <el-table-column prop="phone" label="电话"></el-table-column>
      <el-table-column prop="manuscriptNumber" label="稿件数目"></el-table-column>
      <el-table-column label="操作">
        <template v-slot="{ row }">
          <el-button type="danger" @click="removeWriter(row)">删除</el-button>
        </template>
      </el-table-column>
    </el-table>
  </div>
</template>

<script>
import http from "../axios/http.js"
export default {
  data() {
    return {
      searchNickName: '',
      authors: [],
    };
  },
  methods: {
    searchAuthors() {
        const filteredAuthors = this.authors.filter(author => author.nickName.includes(this.searchNickName));
        this.authors = filteredAuthors;
        if(this.searchNickName === "")
        {
            http.get("/getAllWriter").then
            (response=>{
                this.authors = response.data.writerList;
            }
            )
            .catch(error => {
              console.error('获取作者列表失败', error);
            });
        }
      },
      removeWriter(row){
        console.log(row)
        http.post("/removeWriter",row).then
            (response=>{
                this.authors = response.data.writerList;
            }
            )
            .catch(error => {
              console.error('删除失败', error);
            });
      }
    },
  created() {
      http.get("/getAllWriter").then
      (response=>{
          this.authors = response.data.writerList;
      }
      )
      .catch(error => {
         console.error('获取作者列表失败', error);
       });
  }
};
</script>

<style>
.el-table {
  width: 100%;
}
</style>