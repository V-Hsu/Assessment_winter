import torch
import torch.nn as nn
from torchvision import transforms
from torchvision import datasets
from torch.utils.data import DataLoader
import torch.nn.functional as f
import torch.optim as optim
#import matplotlib.pyplot as plt
batch_size = 100
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.1307,],std=[0.3081,])
])
train_dataset = datasets.MNIST(root='./mnist',train=True,transform=transform,download=True)
test_dataset = datasets.MNIST(root='./mnist',train=False,transform=transform,download=True)

train_dataloader = DataLoader(dataset=train_dataset,batch_size=batch_size,shuffle=True)
test_dataloader = DataLoader(dataset=test_dataset,batch_size=batch_size,shuffle=True)

class Model(nn.Module):
    def __init__(self):
        super(Model, self).__init__()
        self.conv1 = nn.Conv2d(1,10,kernel_size=5)
        self.conv2 = nn.Conv2d(10,20,kernel_size=5)
        self.pooling = nn.MaxPool2d(2)
        self.fc1 = nn.Linear(320,100)
        self.fc2 = nn.Linear(100,50)
        self.fc3 = nn.Linear(50,10)

    def forward(self,x):
        x = f.relu(self.conv1(x))
        x = self.pooling(x)
        x = f.relu(self.conv2(x))
        x = self.pooling(x)
        x = x.view(x.size()[0],-1)
        x = self.fc1(x)
        x = self.fc2(x)
        x = self.fc3(x)
        return x

model = Model()
for m in model.modules():
    if isinstance(m, nn.Linear):
        nn.init.normal_(m.weight, std=0.01)
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
model.to(device)
criterion = nn.CrossEntropyLoss(reduction='mean')
optimizer = optim.SGD(model.parameters(),lr = 0.01,momentum=0.5)

epoch_list = []
def train(epoch):
    running_loss = 0.0
    epoch_list.append(epoch+1)
    for epoch in range(5):
        for i, data in enumerate(train_dataloader, 0):
            input, target = data
            input, target = input.to(device),target.to(device)
            y_pred = model(input)
            loss = criterion(y_pred, target)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            running_loss += loss.item()
            if i % 300 == 299:
                print("{} {} loss:{:.3f}".format(epoch + 1, i + 1, running_loss / 300))
                running_loss = 0.0

accuracy_list = []
def test():
    total = 0
    correct = 0
    with torch.no_grad():
        for i,data in enumerate(test_dataloader,0):
            input,target = data
            input, target = input.to(device), target.to(device)
            y_pred = model(input)
            predicted = torch.argmax(y_pred.data,dim=1)
            total += target.size(0)
            correct += (predicted==target).sum().item()
        accuracy = correct/total
        accuracy_list.append(accuracy)
        print("Accuracy on test set:{:.2f} %".format(100*correct/total))

if __name__ == '__main__':
    for epoch in range(10):
        train(epoch)
        test()
torch.save(model.state_dict,'./wight.pth')
#plt.plot(epoch_list,accuracy_list)
#plt.xlabel('epoch')
#plt.ylabel('accuracy')
#plt.show()