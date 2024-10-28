<template>
  <div>
    <el-table
      :data="tableData"
      style="width: 100%"
      :row-class-name="tableRowClassName"
    >
      <el-table-column prop="manuscriptId" label="稿件id" width="120"> </el-table-column>
      <el-table-column prop="name" label="稿件名称" width="400"></el-table-column>
      <el-table-column prop="categoryId" label="稿件类型id" width="150"> </el-table-column>
      <el-table-column prop="submitTime" label="投递时间" width="180"> </el-table-column>
      <el-table-column prop="latestTime" label="最近更新时间" width="180"> </el-table-column>
      <el-table-column prop="status" label="稿件状态" width="150"> </el-table-column>
      <el-table-column label="操作">
        <template v-slot="{ row }">
          <el-button type="danger" @click="remove(row)">删除</el-button>
          <el-button type="primary" @click="viewDetail(row)">详情</el-button>
        </template>
      </el-table-column>
    </el-table>

    <!-- 小窗口 -->
    <el-dialog title="稿件详情" :visible.sync="dialogFormVisible" :style="{ marginTop: '-120px' }">
      <el-form :data="form">
        <el-form-item label="稿件Id" :label-width="formLabelWidth">
          <el-input v-model="form.manuscriptId" autocomplete="off" disabled></el-input>
        </el-form-item>
        
        <el-form-item label="稿件名" :label-width="formLabelWidth">
          <el-input v-model="form.name" autocomplete="off"></el-input>
        </el-form-item>
        
        <el-form-item label="类别" prop="categoryList" :label-width="formLabelWidth">
            <el-select v-model="form.categoryId" filterable placeholder="请选择">
                <el-option v-for="item in categoryList" :key="item.categoryId" :label="item.name" :value="item.categoryId"></el-option>
            </el-select>
        </el-form-item>

        <el-form-item label="上传时间" :label-width="formLabelWidth">
          <el-input v-model="form.submitTime" autocomplete="off" disabled></el-input>
        </el-form-item>

        <el-form-item label="最近更新时间" :label-width="formLabelWidth">
          <el-input v-model="form.latestTime" autocomplete="off" disabled></el-input>
        </el-form-item>

        <el-form-item label="内容" :label-width="formLabelWidth">
           <el-input v-model="form.description" autocomplete="off" type="textarea" maxlength="500" rows = "10" resize="none"></el-input>
        </el-form-item>

        <el-form-item label="稿件审核评价" :label-width="formLabelWidth">
          <el-input v-model="form.comment" autocomplete="off" type="textarea" maxlength="300" rows = "3" resize="none" disabled></el-input>
        </el-form-item>

        <el-form-item label="审核员" :label-width="formLabelWidth">
          <el-input v-model="form.assessorName" autocomplete="off" disabled></el-input>
        </el-form-item>
      
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button type="primary" @click="dialogFormVisible = false">取消</el-button>
        <el-button type="primary" @click="updateManuscript">更新稿件</el-button>
      </div>
    </el-dialog>
  </div>
</template>

<style>
.el-table .warning-row {
  background: rgb(227, 186, 112);
}

.el-table .success-row {
  background: greenyellow;
}
.el-table .fail-row {
  background: rgb(204, 44, 16);
}
</style>

<script>
import http from '../axios/http.js'
export default {
  methods: {
    tableRowClassName({ row, rowIndex }) {
      if (row.status == 3)//审核中 
      {
        return "warning-row";
      } 
      else if (row.status == 1 )//已公开 
      {
        return "success-row";
      } 
      else if (row.status == 2)//已驳回 
      {
        return "fail-row";
      }
    },
    viewDetail(row){
      this.form.manuscriptId = row.manuscriptId;
      this.form.name = row.name;
      this.form.categoryId = row.categoryId;
      this.form.description = row.description;
      this.form.submitTime = row.submitTime;
      this.form.latestTime = row.latestTime;
      this.form.status = row.status;
      this.form.assessorId = row.assessorId;
      this.form.writerId = row.writerId;
      this.dialogFormVisible = true;
    },
    remove(row){
      http.post("/removePersonalManuscript",row).then
      (response=>{
          this.tableData = response.data.personalManuscriptList;
      }
      )
      .catch(error => {
         console.error('删除个人稿件失败', error);
       });
    },
    updateManuscript()
    {
      http.post("/updatePersonalManuscript",this.form).then
      (response=>{
          this.tableData = response.data.personalManuscriptList;
          this.dialogFormVisible = false
      }
      )
      .catch(error => {
         console.error('更新个人稿件失败', error);
       });
    }
  },
  data() {
    return {
      stopAlter:false,
      tableData: [],
      dialogFormVisible: false,
      categoryList:[],
      form: {
          manuscriptId: "999",          
          name: "关于护额核辐射低洼地就爱节哀2呼呼符合复合如",
          categoryId:1,
          description: "dwfeeeeeeeeeefefeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
          submitTime: "2016-05-02 9:10:50",
          latestTime: "2016-05-02 9:10:50",
          comment:"审核评价",
          status: 2,
          assessorId:-1,
          writerId:0
      },
      formLabelWidth: "120px",
      categoryList:"",
      writerId:0
    };
  },
  created() {
    this.writerId =parseInt(localStorage.getItem("userId"))
    http.post(`/getAllPersonalManuscript`,{"writerId":this.writerId}).then
      (response=>{
          this.tableData = response.data.personalManuscriptList;
      }
      )
      .catch(error => {
         console.error('获取个人稿件列表失败', error);
       });
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