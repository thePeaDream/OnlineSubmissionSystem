<template>
  <el-container>
    <el-header>
      <h2>稿件管理</h2>
    </el-header>
    <el-main>
      <el-table :data="papers" style="margin-top: 20px">
        <el-table-column prop="manuscriptId" label="稿件 ID"></el-table-column>
        <el-table-column prop="name" label="稿件名"></el-table-column>
        <el-table-column prop="submitTime" label="上传时间"></el-table-column>
        <el-table-column prop="latestTime" label="最近修改时间"></el-table-column>
        <el-table-column prop="status" label="稿件状态"></el-table-column>
        <el-table-column prop="writerId" label="作者Id"></el-table-column>
        <el-table-column prop="assessorId" label="审稿人Id"></el-table-column>
        <el-table-column label="操作">
          <template v-slot="{ row }">
            <el-button type="primary" @click="assignAssessor(row)">分配审稿人</el-button>
          </template>
        </el-table-column>

        <!-- 分配审核员对话框 -->
        <el-dialog title="分配审核员" :visible.sync="assignDialogVisible" :append-to-body="true">
          <el-radio-group v-model="selectedAssessorId">
            <!-- assessors 包含所有审核员信息的数组 -->
            <el-radio v-for="assessor in assessors" :key="assessor.assessorId" :label="assessor.assessorId">
              {{ assessor.nickName }}
            </el-radio>
          </el-radio-group>
          <div slot="footer" class="dialog-footer">
            <el-button type="primary" @click="confirmAssign">确认分配</el-button>
            <el-button @click="assignDialogVisible = false">取消</el-button>
          </div>
        </el-dialog>
      </el-table>
    </el-main>
  </el-container>
</template>

<script>
import http from '../axios/http.js'
export default {
  data() {
    return {
      papers: [],
      form: {
        manuscriptId: 1,
        name: "",
        categoryId: 1,
        description: "",
        submitTime: "",
        latestTime: "",
        comment: "",
        status: 2,
        assessorId: -1,
        writerId: 0
      },
      // 新增用于存储选中的审核员 ID
      selectedAssessorId: -1,
      // 新增用于控制分配审核员对话框的显示状态
      assignDialogVisible: false,
      // 存储所有审核员信息的数组
      assessors: []
    };
  },
  methods: {
    viewPaper(paper) {
      // 逻辑以查看稿件详情
      this.$message.info(`查看稿件: ${paper.name}`);
    },
    assignAssessor(row) {
      console.log(row)
      console.log(this.assessors)
      // 打开分配审核员对话框并设置稿件 ID
      this.selectedAssessorId = null;
      this.assignDialogVisible = true;
      this.form.manuscriptId = row.manuscriptId;
    },
    confirmAssign() {
      const manuscriptId = this.form.manuscriptId;
      const assessorId = this.selectedAssessorId;
      http.post(`/assignAssessor`, { manuscriptId, assessorId })
       .then(response => {
          this.papers = response.data.manuscriptList;
          this.assignDialogVisible = false;
        })
       .catch(error => {
          console.error('给稿件分配审核员失败', error);
        });
    }
  },
  async created() {
    try {
      const response1 = await http.get(`/getAllManuscript`);
      this.papers = response1.data.manuscriptList;
      console.log("获取所有稿件成功");

      const response2 = await http.get("/getFormalAssessor");
      this.assessors = response2.data.formalAssessorList;
      console.log("获取审核员列表成功");
    } catch (error) {
      console.error('获取数据失败', error);
    }
  }
  
};
</script>

<style scoped>
.el-table {
  width: 100%;
}
</style>
