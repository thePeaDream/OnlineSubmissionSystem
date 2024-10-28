<template>
  <el-card>
    <h2>稿件管理</h2>
    <el-tabs v-model="activeTab">
      <el-tab-pane label="待审核" name="pending">
        <el-table :data="pendingManuscripts" style="width: 100%">
          <el-table-column prop="manuscriptId" label="稿件Id" />
          <el-table-column prop="name" label="稿件名" />
          <el-table-column prop="submitTime" label="提交时间" />
          <el-table-column prop="latestTime" label="最新更新时间" />
          <el-table-column prop="writerId" label="作者Id" />
          <el-table-column>
            <template v-slot="scope">
              <el-button @click="auditMenuscript(scope.row)">审核</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-tab-pane>
      <el-tab-pane label="已审核" name="approved">
        <el-table :data="approvedManuscripts" style="width: 100%">
          <el-table-column prop="manuscriptId" label="稿件Id" />
          <el-table-column prop="name" label="稿件名" />
          <el-table-column prop="submitTime" label="提交时间" />
          <el-table-column prop="latestTime" label="最新更新时间" />
          <el-table-column prop="writerId" label="作者Id" />
          <el-table-column prop="status" label="状态" />
          <el-table-column>
            <template v-slot="scope">
              <el-button @click="auditMenuscript(scope.row)">详情</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-tab-pane>
    </el-tabs>

    <!-- 审核框模态框 -->
    <el-dialog title="审核稿件" :visible.sync="auditDialogVisible" style="margin-top=-100px;">
      <el-form :model="auditForm">
        <el-form-item label="稿件名">
          <el-input v-model="auditForm.name" disabled></el-input>
        </el-form-item>
        <el-form-item label="内容">
          <el-input type="textarea" v-model="auditForm.description" maxlength="300" rows = "10" resize="none" disabled></el-input>
        </el-form-item>
        <el-form-item label="稿件Id">
          <el-input v-model="auditForm.manuscriptId" disabled></el-input>
        </el-form-item>
        <el-form-item label="审核评价">
          <el-input v-model="auditForm.comment" autocomplete="off"></el-input>
        </el-form-item>
        <el-form-item label="稿件状态">
          <el-select v-model="auditForm.status" placeholder="请选择稿件状态">
            <el-option label="公开" :value="1"></el-option>
            <el-option label="驳回" :value="2"></el-option>
            <el-option label="待审核" :value="3"></el-option>
          </el-select>
        </el-form-item>
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button type="primary" @click="confirmAudit">确认审核</el-button>
        <el-button @click="auditDialogVisible = false">取消</el-button>
      </div>
    </el-dialog>

  </el-card>
</template>

<script>
import http from '../axios/http.js'
export default {
  data() {
    return {
      activeTab: 'pending',
      ManuscriptList:[],
      auditForm: {
        name: '',
        manuscriptId: '',
        comment: '',
        description:'',
        status: 1,
        assessorId:0
      },
      auditDialogVisible:false
    };
  },
  methods: {
    auditMenuscript(article) {
      // 填充审核框的信息
      this.auditForm.assessorId =article.assessorId;
      this.auditForm.name = article.name;
      this.auditForm.manuscriptId = article.manuscriptId;
      this.auditForm.comment = article.comment; // 可以根据实际情况设置默认值
      this.auditForm.status = article.status; 
      this.auditForm.description = article.description;
      this.auditDialogVisible = true;
    },
    confirmAudit(){
      http.post(`/setManuscriptStatus`, this.auditForm)
      .then(response => {
          // 审核成功后的处理，刷新稿件列表
          this.ManuscriptList = response.data.auditManuscriptList;
          this.auditDialogVisible = false;
        })
      .catch(error => {
          console.error('审核更新失败', error);
        });
    }
  },
  computed: {
     pendingManuscripts() {
       if(this.ManuscriptList == null)
          this.ManuscriptList = []
       return this.ManuscriptList.filter(item => item.status == 3);
     },
     approvedManuscripts() {
      if(this.ManuscriptList == null)
          this.ManuscriptList = []
       return this.ManuscriptList.filter(item => item.status != 3);
     }
   },
   created() {
    this.assessorId =parseInt(localStorage.getItem("userId"))
    http.post(`/getAuditManuscript`,{"assessorId":this.assessorId}).then
      (response=>{
        console.log(response)
          this.ManuscriptList = response.data.auditManuscriptList;
      }
      )
      .catch(error => {
         console.error('获取待审核稿件列表失败', error);
       });
  },
};
</script>

<style scoped>
h2 {
  margin-bottom: 20px;
}
</style>