<template>
    <div> 
        <div class="frame" id="target-list">
            <div class="list-box">
                전환
                <img src="@/assets/addBtn2.png" class="icon add-icon" @click="addList(0)">
                <div class="list-content-group">
                    <!-- <div id="default-translist" v-if="transListNum ==0 && add[1]!=0">
                        <img src="@/assets/exclamationMark.png" style="width:7vh; margin: 13vh 15.5vw 2vh 15.5vw">
                        <div style="text-align: center;">데이터를 추가해주세요</div>
                    </div> -->
                    <div class='list-content' v-for = "trans in targetList" v-on:mouseover="hoverTarget(trans)" v-on:mouseleave="leaveTarget()"> 
                        <span v-if="trans.listkind==0">
                            <span class="direction-icon">▶</span>
                            <!-- 리스트 내용 -->
                            <span class="list-content-text" v-if="edit[0]==false||edit[1]!=trans.index">{{ trans.category }}의 {{ trans.percentage}}%를 {{ trans.target }}로 전환</span>
                            <!-- hover시 -->
                            <div class="target-icon" v-if="select==trans.index && trans.listkind==0">
                                <img src="@/assets/editBtn.png" v-if="edit[0]==false||edit[1]!=trans.index" @click="clickEditTarget(trans)">
                                <img style="margin:0vh 1vw" src="@/assets/deleteBtn.png" v-if="edit[0]==false||edit[1]!=trans.index" @click="clickDeleteTarget(trans)">
                            </div>
                        </span>
                        <!-- 리스트 수정 -->
                        <span class="list-content-text" v-if="edit[0]==true && edit[1]==trans.index &&trans.listkind==0" v-on:keyup.enter="submitEdit(trans)">
                            <select v-model="category" class="box drop-box" >
                                <option>전력</option>
                            </select> 의 <input class="box input-box" id="transPercent" placeholder='30'> %를
                            <select v-model="transEnargy" class="box drop-box" >
                                <option :value=trans v-for="trans in transEnargyList">{{trans}}</option >
                            </select> 로 전환
                        </span> 
                    </div>
                    <!-- 리스트 추가 -->
                    <div class='list-content' v-if="add[0]==true && add[1]==0">
                        <span class="list-content-text" v-on:keyup.enter="submitAdd()">
                            <select v-model="category" class="box drop-box" >
                                <option>전력</option>
                            </select> 의 <input class="box input-box " id="transPercent" placeholder='30'> %를
                            <select v-model="transEnargy" class="box drop-box" >
                                <option :value=trans v-for="trans in transEnargyList">{{trans}}</option >
                            </select> 로 전환
                        </span> 
                    </div>
                </div>
            </div>
            <div class = "line"></div>
            <div class="list-box increse-box">
                감축
                <img src="@/assets/addBtn2.png" class="icon add-icon" @click="addList(1)">
                <div class="list-content-group">
                    <!-- <div id="default-increaslist" v-if="increasListNum ==0 && add[1]!=1">
                        <img src="@/assets/exclamationMark.png" style="width:7vh; margin: 13vh 13vw 2vh 13vw">
                        <div style="text-align: center;">데이터를 추가해주세요</div>
                    </div> -->
                    <div class ="list-content" v-for = "increas in targetList" v-on:mouseover="hoverTarget(increas)" v-on:mouseleave="leaveTarget()">
                        <span v-if="increas.listkind==1">
                            <span class="direction-icon">▶</span>
                            <!-- 리스트 내용 -->
                            <span class="list-content-text" v-if="edit[0]==false||edit[1]!=increas.index">{{increas.category}}의 {{increas.percentage}}%를 감축</span>
                            <div class="target-icon" v-if = "select==increas.index && increas.listkind==1">
                                <img src="@/assets/editBtn.png" v-if="edit[0]==false||edit[1]!=increas.index" @click="clickEditTarget(increas)">
                                <img  style="margin:0vh 1vw" src="@/assets/deleteBtn.png" v-if="edit[0]==false||edit[1]!=increas.index" @click="clickDeleteTarget(increas)">
                            </div>
                        </span>
                        
                        <!-- 리스트 수정 -->
                        <span class="list-content-text" v-if="edit[0]==true && edit[1]==increas.index && increas.listkind==1" v-on:keyup.enter="submitEdit(increas)">
                            <select v-model="category" class="box drop-box" >
                                <option :value="cate" v-for="cate in categoryList">{{ cate }}</option>
                            </select> 의 <input class="box input-box" id="increasPercent" placeholder='30'> %를 감축
                        </span> 
                    </div>
                    <!-- 리스트 추가 -->
                    <div class='list-content' v-if="add[0]==true && add[1]==1">
                        <span class="list-content-text" v-on:keyup.enter="submitAdd('감축')">
                            <select v-model="category" class="box drop-box" >
                                <option :value="cate" v-for="cate in categoryList">{{ cate }}</option>
                            </select> 의 <input class="box input-box" id="increasPercent" placeholder='30'> %를 감축
                        </span> 
                    </div>
                </div>
            </div>
        
            <button :class="{clickbtn: editContent, 'nonclickbtn': !editContent}" id="target-add-btn" @click="clickSaveTarget()">저장하기</button>
            <!-- <button class="clickbtn" id="target-add-btn" @click="clickOpenAddTarget()">+ 추가하기</button> -->
        </div>
    </div>
        

</template>



<script>
import { useStore } from 'vuex'
import {computed, ref} from 'vue'
import axios from "axios";
    export default {
        name :"target_dash1",
        components:{
        },
        setup(){
            const store = useStore();

            //날짜 그룹명
            var config = {
                headers:{
                "Authorization":"Bearer"+" "+store.state.accessToken,
                }
            }
            var selected_company = computed(()=> store.state.insight_selected_company)
            var now = new Date();
            var year_now = now.getFullYear()
            var month_now = now.getMonth()

            //수정, 삭제, 추가에 대한 변수
            var editContent = ref(false); //리스트 변경사항이 있는지 확인하는 변수
            var del_id = []; 
            var edit_id = []; 
            var edit = ref([false, -1]); 
            var del = ref([false, -1]);
            var add = ref([false,-1])

            //수정과 추가시 선택하는데 필요한 리스트
            var categoryList= computed(() => store.state.CarbonCategories)
            var transEnargyList = [
                '풍력 에너지',
                '태양광 에너지'
            ]
            var category =ref('고정연소')
            var transEnargy =ref('태양열 에너지')
            var re = ref(0)
            //서버, 사용자의 전환, 감축 목표 리스트

            async function get_target_list(){
                var url = "/CarbonNature/TargetList/"+selected_company.value+"/"+year_now
                axios.get(url,config).then(res=>{
                    store.commit("getTargetList", res.data)
                })
                .catch(error => {
                    console.log(error)
                })
                .finally(()=>{
                })
                
            }
            get_target_list()
            var targetList = computed(() => store.state.getTargetList)
    
            //각각의 리스트 내용의 개수를 나타내는 변수
            var transListNum = ref(targetList.value.filter(list => list.listkind === 0).length) 
            var increasListNum = ref(targetList.value.filter(list => list.listkind === 1).length)


            var select =ref(-1) // 마우스가 가리키고있는 리스트 내용

            //마우스 오버시 수정, 삭제 기능 옵션 on
            const hoverTarget=(value)=>{
                select.value = value.index
            }

            //마우스 오버시 수정, 삭제 기능 옵션 off
            const leaveTarget=()=>{
                select.value = -1
            }

            //추가하기 버튼 클릭시 추가 폼 여는 함수
            function addList(kind_){
                add.value[0]=true
                add.value[1]=kind_   
            }

            //수정하기 버튼 클릭시 수정 폼 여는 함수
            function clickEditTarget(list){
                edit.value[0] = true
                edit.value[1] = list.index
            }

            //추가 완료후 리스트 업
            function submitAdd(){
                var addIndex = targetList.value.length
                if(add.value[1]==0){
                    targetList.value.push({
                        listkind:0, 
                        index:addIndex, 
                        i:'',
                        category:category.value, 
                        percentage: parseInt(document.getElementById('transPercent').value),
                        target: transEnargy.value
                    })
                    
                    editContent.value = true
                    transListNum.value = targetList.value.filter(list => list.listkind === 0).length
                }
                else{
                    targetList.value.push({
                        listkind:1, 
                        index:addIndex, 
                        i:'',
                        category:category.value, 
                        percentage: parseInt(document.getElementById('increasPercent').value), 
                        target: ''
                    })
                    editContent.value = true
                    increasListNum.value = targetList.value.filter(list => list.listkind === 1).length
                }
                add.value[0]=false
                add.value[1]=-1  
                
            }

            //수정 완료후 리스트 업
            function submitEdit(list){
                if(list.listkind==0){
                    targetList.value[list.index] = {
                        listkind:list.listkind, 
                        index:list.index, 
                        i:list.id,
                        category:category.value, 
                        percentage: parseInt(document.getElementById('transPercent').value),
                        target: transEnargy.value
                    }
                }
                else{
                    targetList.value[list.index] = {
                        listkind:list.listkind, 
                        index:list.index,
                        i:list.id, 
                        category:category.value, 
                        percentage: parseInt(document.getElementById('increasPercent').value),
                        target: ''
                    }
                }
                if(list.i != ''){
                    edit_id.push(list.i)
                }
 
                edit.value[0]=false
                edit.value[1]=-1
                editContent.value = true
  
            }

            //리스트 삭제 함수
            function clickDeleteTarget(list){
                //서버에 저장되어있던 감축 목표가 삭제 되었을 때만 id를 저장
                if(list.i != ''){
                    del_id.push(list.i)
                }
           
                targetList.value.splice(list.index, 1);
                editContent.value=true

                for(var i=list.index; i<targetList.value.length; i++){
                    targetList.value[i].index=targetList.value[i].index-1
                }
                transListNum.value = targetList.value.filter(list => list.listkind === 0).length
                increasListNum.value = targetList.value.filter(list => list.listkind === 1).length
                
            }

            //서버에 저장
            function clickSaveTarget(){
                editContent.value=false
                
                var server_add_list = []
                for (var i=0; i < targetList.value.length; i++){
                    if(targetList.value[i].i ==''){
                        server_add_list.push(targetList.value[i])
                    }               
                }  
                var post_targetList = {
                    groupName : selected_company.value,
                    year : year_now,
                    tList:server_add_list
                }
                set_target_list(post_targetList)
                
            }

       

            async function set_target_list(list){
                var url = "/CarbonNature/TargetList"
                axios.post(url,list,config).then(res=>{
                })
                .catch(error => {
                    console.log(error)
                })
                .finally(()=>{
                    store.commit("setReload")
                })
            }
            


            return{
                targetList,
                hoverTarget,
                leaveTarget,
                clickSaveTarget,
                clickEditTarget,
                select,
                categoryList,
                category,
                edit,
                add,
                submitEdit,
                submitAdd,
                addList,
                clickDeleteTarget,
                editContent,
                transEnargy,
                transEnargyList,
                transListNum,
                increasListNum,
                get_target_list,
                re

            }
        },
        mounted(){

        }
    }
</script>

<style>
.clickbtn{
    background: #3DC984;
    border: none;
    border-radius: 1vh;
    width:8vw;
    height: 5vh;
    color:white
}
.clickbtn:hover{
    cursor: pointer;
}
.nonclickbtn{
    background: #AEAEAE;
    border: none;
    border-radius: 1vh;
    width:8vw;
    height: 5vh;
    color:white
}
#target-list{
    margin-top:1px;
    min-height:60vh;
    width:71vw;
    padding:5vh 4vw
}
.list-box{
    font-size:1.5rem; 
    font-weight: bold;
    float:left; 
    width:35vw; 
    min-height: 57vh;
}
.increse-box{
    width:29.9vw;
}
.line{
    min-height: 60vh; 
    width:1px;
    background:#EEEEEF; 
    float:left; 
    margin:0 3vw
}
.list-content-group{
    overflow: auto;
    height: 45.7vh;
    margin-top:8vh; 
    font-size:1.1rem; 
    font-weight: 400 ;
}
.direction-icon{
    display:inline-block;
    color:#3DC984; 
    margin:3.5vh 1vw;
}
.list-content-text{
   font-size:1.1rem
}
.list-content:hover{
    border-radius: 2vh;
    background: #f0f0f0;
}
.box{
    height:4vh;
    width:7vw;
    font-size:1rem;
    border-radius: 0.7vh;
    border: 1px solid #D0D0D0;
}
.input-box{
    height: 3.7vh;
    width:3vw;
}
.drop-box{
    background: #EFF1F9;
    border: none;
}
.long-drop-box{
    width:10vw
}
#target-add-btn{
    float:right;
}
.icon{
    height:4vh;
}
.icon:hover{
    cursor: pointer;
}
.add-icon{
    float:right
}
.target-icon{
    display:inline-block; 
    float: right; 
    margin-top:2.7vh
}
.target-icon> img{
    height:4vh;
}
.target-icon> img:hover{
    cursor: pointer;
}
#default-translist{
    width:inherit; 
    height:40vh; 
    border:1px solid #d5d5d5; 
    border-radius: 2vh;
}
#default-increaslist{
    width:inherit; 
    height:40vh; 
    border:1px solid #d5d5d5; 
    border-radius: 2vh;
}
</style>
