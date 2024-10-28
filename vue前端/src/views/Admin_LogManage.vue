<template>
  <el-container>
    <el-header>
      <h2>日志管理</h2>
    </el-header>
    <el-main>
      <el-table :data="papers" style="margin-top: 20px">
        <el-table-column prop="logId" label="日志Id"></el-table-column>
        <el-table-column prop="operate" label="操作"></el-table-column>       
        <el-table-column prop="operateTime" label="操作时间"></el-table-column>
        <el-table-column label="操作">
          <template v-slot="{ row }">
            <el-button type="danger" @click="deletePaper(row)">删除</el-button>
          </template>
        </el-table-column>
      </el-table>
    </el-main>
  </el-container>
</template>

<script>
import http from "../axios/http.js"
export default {
  data() {
    return {
      papers: []
    };
  },
  methods: {
    deletePaper(paper) 
    {
        http.post("/removeLog",paper).then
        (response=>{
            this.papers = response.data.logList;
          }
        )
      .catch(error => {
         console.error('请求日志发生错误', error);
       });
    }
  },
  created() {
      http.get("/getAllLog").then
      (response=>{
          this.papers = response.data.logList;
      }
      )
      .catch(error => {
         console.error('请求日志发生错误', error);
       });
  },
};
</script>

<style scoped>
.el-table {
  width: 100%;
}
</style>