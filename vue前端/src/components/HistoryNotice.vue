<template>
  <div>
    <el-table
      :data="tableData"
      style="width: 100%"
    >
      <el-table-column prop="noticeId" label="通知编号" width="180"> </el-table-column>
      <el-table-column prop="title" label="通知标题" width="400"></el-table-column>
      <el-table-column prop="publishTime" label="发布时间" width="250"> </el-table-column>
      <el-table-column prop="latestTime" label="最新修改时间" width="180"> </el-table-column>
      <el-table-column fixed="right" label="操作" width="200">
        <template slot-scope="scope">
          <el-button type="text" @click="showNoticeDetails(scope.row)" >详情</el-button>
          <template v-if="isAdmin">
            <el-button type="text" @click="showEditDialog(scope.row)">修改</el-button>
            <el-button type="text" @click="deleteNotice(scope.row)">删除</el-button>
          </template>
        </template>
      </el-table-column>
    </el-table>

    <!-- 通知详情对话框 -->
    <el-dialog title="通知详情" :visible.sync="dialogVisible">
      <el-form :data="form">
        <el-form-item label="通知编号" :label-width="formLabelWidth">
          <el-input v-model="form.noticeId" autocomplete="off" disabled></el-input>
        </el-form-item>
        <el-form-item label="通知标题" :label-width="formLabelWidth">
          <el-input v-model="form.title" autocomplete="off" disabled></el-input>
        </el-form-item>
        <el-form-item label="发布时间" :label-width="formLabelWidth">
          <el-input v-model="form.publishTime" autocomplete="off" disabled></el-input>
        </el-form-item>
        <el-form-item label="最新修改时间" :label-width="formLabelWidth">
          <el-input v-model="form.latestTime" autocomplete="off" disabled></el-input>
        </el-form-item>
        <el-form-item label="通知内容" :label-width="formLabelWidth">
          <el-input v-model="form.content" autocomplete="off" type="textarea" maxlength="300" rows="5" resize="none" disabled></el-input>
        </el-form-item>
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button type="primary" @click="dialogVisible = false">关闭</el-button>
      </div>
    </el-dialog>

    <!-- 修改通知对话框 -->
    <el-dialog title="修改通知" :visible.sync="editDialogVisible">
      <el-form :data="editForm">
        <el-form-item label="通知编号" :label-width="formLabelWidth">
          <el-input v-model="editForm.noticeId" autocomplete="off" disabled></el-input>
        </el-form-item>
        <el-form-item label="通知标题" :label-width="formLabelWidth">
          <el-input v-model="editForm.title" autocomplete="off"></el-input>
        </el-form-item>
        <el-form-item label="通知内容" :label-width="formLabelWidth">
          <el-input v-model="editForm.content" autocomplete="off" type="textarea" maxlength="300" rows="5" resize="none"></el-input>
        </el-form-item>
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button @click="editDialogVisible = false">取消</el-button>
        <el-button type="primary" @click="saveEditedNotice">确定</el-button>
      </div>
    </el-dialog>
  </div>
</template>

<script>
import http from '../axios/http.js'
export default {
  data() {
    return {
      tableData: [],
      dialogVisible: false,
      form: {
        noticeId: null,
        title: null,
        publishTime: null,
        latestTime: null,
        content: null,
      },
      formLabelWidth: "120px",
      role: 1,
      editDialogVisible: false,
      editForm: {
        noticeId: null,
        title: null,
        content: null,
      }
    };
  },
  methods: {
    showNoticeDetails(row) {
      this.form.noticeId = row.noticeId;
      this.form.title = row.title;
      this.form.publishTime = row.publishTime;
      this.form.latestTime = row.latestTime;
      this.form.content = row.content;
      this.dialogVisible = true;
    },
    showEditDialog(row) {
      this.editForm.noticeId = row.noticeId;
      this.editForm.title = row.title;
      this.editForm.content = row.content;
      this.editDialogVisible = true;
    },
    deleteNotice(row) {
      http.post("/removeNotice",row).then
      (response=>{
          this.tableData = response.data.noticeList;
      }
      )
      .catch(error => {
         console.error('获取通知列表发生错误', error);
       });
    },
    saveEditedNotice() {
      http.post("/updateNotice",this.editForm).then
      (response=>{
          this.tableData = response.data.noticeList;
      }
      )
      .catch(error => {
         console.error('获取通知列表发生错误', error);
       });
       this.editDialogVisible = false
    },
  },
  created() {
    http.get("/getAllNotice").then
      (response=>{
        console.log(response)
        this.tableData = response.data.noticeList;
      }
      )
      .catch(error => {
         console.error('获取通知列表发生错误', error);
       });
    this.role = localStorage.getItem('role')
  },
  computed: {
    isAdmin() {
      return this.role == 3;
    }
  }
};
</script>

<style>
.el-table.warning-row {
  background: rgb(227, 186, 112);
}

.el-table.success-row {
  background: greenyellow;
}

.el-table.fail-row {
  background: rgb(204, 44, 16);
}
</style>