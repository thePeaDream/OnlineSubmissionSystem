<template>
  <div>
    <el-row v-for="item in articles" :key="item.manuscriptId" style="display: flex; justify-content: center;">
      <el-col :span="14">
        <div class="article-item" style="margin: 10px 20px;background-color: aqua;">
          <h3>{{item.name}}</h3>
          <p style="margin-top: 10px;">类别：{{item.categoryId}}</p>
          <p style="margin-top: 10px;">发布时间：{{item.submitTime}}</p>
          <p style="margin-top: 10px;">更新时间：{{item.latestTime}}</p>
          <p style="margin-top: 10px;">稿件内容：{{item.description}}</p>
        </div>
      </el-col>
    </el-row>
  </div>
</template>

<script>
import http from '../axios/http.js'

export default {
  data() {
    return {
      searchQuery: '',
      articles: []
    };
  },
  computed: {
  
  },
  methods: {
    searchManuscripts() {
      
    }
  },
  created()
  {
    http.get(`/getAllPublishManuscript`).then
      (response=>{
        console.log(response)
          this.articles = response.data.publishManuscriptList;
      }
      )
      .catch(error => {
         console.error('获取审核员列表失败', error);
       });
  }
};
</script>

<style scoped>
.article-item {
  border: 1px solid #ddd;
  padding: 10px;
  margin-bottom: 20px;
}
</style>